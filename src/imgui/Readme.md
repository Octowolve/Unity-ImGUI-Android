# [ImGUI](https://github.com/ocornut/imgui)

Add the imgui files here. In this project OpenGLv3 is used so download its corresponding backend files.

You have to add to functions.


1. Handle Input

```
int32_t ImGui_ImplAndroid_HandleInputEvent(int motion_event, int x, int y, int pointer)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(x, y);

    switch(motion_event){
        case 2:
            if (pointer > 1) {
                io.MouseDown[0] = false;
            }
            else {
                io.MouseWheel = 0;
            }
            break;
        case 1:
            io.MouseDown[0] = false;
            break;
        case 0:
            io.MouseDown[0] = true;
            break;

    }

    return 0;
}
```

Since we are not using android's input events we have to handle the input ourself.


2. New Frame

```
void ImGui_ImplAndroid_NewFrame(int x, int y)
{
    ImGuiIO& io = ImGui::GetIO();

    // Process queued key events
    // FIXME: This is a workaround for multiple key event actions occurring at once (see above) and can be removed once we use upcoming input queue.
    for (auto& key_queue : g_KeyEventQueues)
    {
        if (key_queue.second.empty())
            continue;
        io.KeysDown[key_queue.first] = (key_queue.second.front() == AKEY_EVENT_ACTION_DOWN);
        key_queue.second.pop();
    }

    // Setup display size (every frame to accommodate for window resizing)
    int32_t window_width = x;
    int32_t window_height = y;
    int display_width = window_width;
    int display_height = window_height;

    io.DisplaySize = ImVec2((float)window_width, (float)window_height);
    if (window_width > 0 && window_height > 0)
        io.DisplayFramebufferScale = ImVec2((float)display_width / window_width, (float)display_height / window_height);

    // Setup time step
    struct timespec current_timespec;
    clock_gettime(CLOCK_MONOTONIC, &current_timespec);
    double current_time = (double)(current_timespec.tv_sec) + (current_timespec.tv_nsec / 1000000000.0);
    io.DeltaTime = g_Time > 0.0 ? (float)(current_time - g_Time) : (float)(1.0f / 60.0f);
    g_Time = current_time;
}
```

Since we are not using android's native window we have to set the window height and width in another way
