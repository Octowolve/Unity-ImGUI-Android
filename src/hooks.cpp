#include "includes/hooks.h"

namespace hooks {
	swapbuffers::orig o_swapbuffers = nullptr;
	input::inject_event::orig o_inject_event = nullptr;

	void* init(void*) {
		LOGI("2");
		const char* lib_EGL = "libEGL.so";

		do {
			sleep(1);
		} while (!utils::is_library_loaded(lib_EGL));

		void* swap_buffers_addr = DobbySymbolResolver(lib_EGL, "eglSwapBuffers");
		if (swap_buffers_addr == NULL)
			return NULL;

		if (DobbyHook(reinterpret_cast<void*>(swap_buffers_addr), reinterpret_cast<void*>(swapbuffers::hook),
					  reinterpret_cast<void**>(&o_swapbuffers)) != 0)
			return NULL;

		const char* lib_unity = "libunity.so";

		do {
			sleep(1);
		} while (!utils::is_library_loaded(lib_unity));
		
		//refer to "Tutorials/Get nativeInject Event Signature.md" to understand this
		uintptr_t inject_event = utils::find_pattern_in_module(lib_unity, "70 40 2D E9 10 D0 4D E2 02 50 A0 E1 7E CE FF EB");
		if(inject_event == NULL)
			return NULL;

		if (DobbyHook(reinterpret_cast<void*>(inject_event), reinterpret_cast<void*>(input::inject_event::hook),
					  reinterpret_cast<void**>(&o_inject_event)) != 0)
			return NULL;

		LOGI("hooks initialized");
		return NULL;
	}

	EGLBoolean swapbuffers::hook(EGLDisplay dpy, EGLSurface surf) {
		EGLint w, h;
		eglQuerySurface(dpy, surf, EGL_WIDTH, &w);
		eglQuerySurface(dpy, surf, EGL_HEIGHT, &h);

		menu::setup_menu();
		menu::draw_menu(w, h);
		
		return o_swapbuffers(dpy, surf);
	}

	int input::inject_event::hook(JNIEnv *env, jobject __this, jobject input_event) {
		jclass motion_event = env->FindClass(("android/view/MotionEvent"));

		if(!motion_event){
			LOGI("Can't find MotionEvent!");
			return o_inject_event(env, __this, input_event);
		}

		if(env->IsInstanceOf(input_event, motion_event)){
			jmethodID get_action = env->GetMethodID(motion_event, ("getActionMasked"), ("()I"));
			jmethodID get_x = env->GetMethodID(motion_event, ("getX"), ("()F"));
			jmethodID get_y = env->GetMethodID(motion_event, ("getY"), ("()F"));
			jmethodID get_pointer_count = env->GetMethodID(motion_event, ("getPointerCount"), ("()I"));

			ImGui_ImplAndroid_HandleInputEvent(env->CallIntMethod(input_event, get_action),env->CallFloatMethod(input_event, get_x), env->CallFloatMethod(input_event, get_y), env->CallIntMethod(input_event, get_pointer_count));

			ImGuiIO &io = ImGui::GetIO();
			if (io.WantCaptureMouse)
				return true;
		}

		jclass key_event = env->FindClass("android/view/KeyEvent");

		if(!key_event){
			LOGI("Can't find KeyEvent!");
			return o_inject_event(env, __this, input_event);
		}

		if(env->IsInstanceOf(input_event, key_event)){
			jmethodID get_unicode_char = env->GetMethodID(key_event, ("getUnicodeChar"), ("()I"));
			jmethodID get_meta_state = env->GetMethodID(key_event, ("getMetaState"), ("()I"));

			ImGuiIO &io = ImGui::GetIO();
			io.AddInputCharacter(env->CallIntMethod(input_event, get_unicode_char, env->CallIntMethod(input_event, get_meta_state)));
		}
		return o_inject_event(env, __this, input_event);
	}
}
