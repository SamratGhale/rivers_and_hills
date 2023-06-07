
/*
	TODO: Create window for following opengl tutorial
*/

#include "main.h"
#include "glm/ext.hpp"

global_variable bool running;


function void win32_init_opengl(HWND window) {
	HDC hdc = GetDC(window);

	PIXELFORMATDESCRIPTOR desired_pixel_format = {};

	desired_pixel_format.nSize = sizeof(desired_pixel_format);
	desired_pixel_format.nVersion = 1;
	desired_pixel_format.dwFlags =
		PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	desired_pixel_format.iPixelType = PFD_TYPE_RGBA;
	desired_pixel_format.cColorBits = 32;
	desired_pixel_format.cAlphaBits = 8;
	desired_pixel_format.iLayerType = PFD_MAIN_PLANE;

	s32 suggested_pixel_format_index =
		ChoosePixelFormat(hdc, &desired_pixel_format);
	PIXELFORMATDESCRIPTOR suggested_pixel_format;
	DescribePixelFormat(hdc, suggested_pixel_format_index,
		sizeof(suggested_pixel_format), &suggested_pixel_format);
	SetPixelFormat(hdc, suggested_pixel_format_index,
		&suggested_pixel_format);
	HGLRC opengl_rc = wglCreateContext(hdc);
	if (wglMakeCurrent(hdc, opengl_rc)) {
		b32 modern_context = false;
		wgl_create_context_attribs_arb* wglCreateContextAttribsARB =
			(wgl_create_context_attribs_arb*)wglGetProcAddress(
				"wglCreateContextAttribsARB");

		glAttachShader = (gl_attach_shader*)wglGetProcAddress("glAttachShader");
		glCompileShader = (gl_compile_shader*)wglGetProcAddress("glCompileShader");
		glCreateProgram = (gl_create_program*)wglGetProcAddress("glCreateProgram");
		glCreateShader = (gl_create_shader*)wglGetProcAddress("glCreateShader");
		glDeleteProgram = (gl_delete_program*)wglGetProcAddress("glDeleteProgram");
		glLinkProgram = (gl_link_program*)wglGetProcAddress("glLinkProgram");
		glShaderSource = (gl_shader_source*)wglGetProcAddress("glShaderSource");
		glUseProgram = (gl_use_program*)wglGetProcAddress("glUseProgram");
		glValidateProgram =
			(gl_validate_program*)wglGetProcAddress("glValidateProgram");
		glGetProgramiv = (gl_get_programiv*)wglGetProcAddress("glGetProgramiv");
		glGetProgramInfoLog =
			(gl_get_program_info_log*)wglGetProcAddress("glGetProgramInfoLog");
		glGetShaderInfoLog =
			(gl_get_shader_info_log*)wglGetProcAddress("glGetShaderInfoLog");
		glGetUniformLocation =
			(gl_get_uniform_location*)wglGetProcAddress("glGetUniformLocation");
		glGetUniformiv = (gl_get_uniform_iv*)wglGetProcAddress("glGetUniformiv");
		glUniform1i = (gl_uniform_1i*)wglGetProcAddress("glUniform1i");
		glUniform4f = (gl_uniform_4f*)wglGetProcAddress("glUniform4f");
		glUniform2i = (gl_uniform_2i*)wglGetProcAddress("glUniform2i");
		glUniformMatrix4fv =
			(gl_uniform_matrix_4fv*)wglGetProcAddress("glUniformMatrix4fv");
		glBindVertexArray =
			(gl_bind_vertex_array*)wglGetProcAddress("glBindVertexArray");
		glGenVertexArrays =
			(gl_gen_vertex_arrays*)wglGetProcAddress("glGenVertexArrays");
		glGenBuffers = (gl_gen_buffers*)wglGetProcAddress("glGenBuffers");
		glBindBuffer = (gl_bind_buffer*)wglGetProcAddress("glBindBuffer");
		glBufferData = (gl_buffer_data*)wglGetProcAddress("glBufferData");
		glVertexAttribPointer =
			(gl_vertex_attrib_pointer*)wglGetProcAddress("glVertexAttribPointer");
		glEnableVertexAttribArray =
			(gl_enable_vertex_attrib_array*)wglGetProcAddress(
				"glEnableVertexAttribArray");
		glActivateTexture =
			(gl_active_texture*)wglGetProcAddress("glActiveTexture");

		glUniform2f = (gl_uniform_2f*)wglGetProcAddress("glUniform2f");
		glBufferSubData = (gl_buffer_sub_data*)wglGetProcAddress("glBufferSubData");
		glGenerateMipmap = (gl_generate_mipmap*)wglGetProcAddress("glGenerateMipmap");
		// glGetProgramInfoLog =
		// (gl_get_program_info_log*)wglGetProcAddress("glGetProgramInfoLog");

		if (wglCreateContextAttribsARB) {
			int attribs[] = {
				WGL_CONTEXT_MAJOR_VERSION_ARB,
				3,
				WGL_CONTEXT_MINOR_VERSION_ARB,
				0,
				WGL_CONTEXT_FLAGS_ARB,
				0 | WGL_CONTEXT_DEBUG_BIT_ARB,  // Note:enable for debugging
				WGL_CONTEXT_PROFILE_MASK_ARB,
				WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
				0,
			};

			HGLRC share_context = 0;
			HGLRC modern_glrc =
				wglCreateContextAttribsARB(hdc, share_context, attribs);
			if (modern_glrc) {
				if (wglMakeCurrent(hdc, modern_glrc)) {
					modern_context = true;
					wglDeleteContext(opengl_rc);
					opengl_rc = modern_glrc;
				}
			}
		}
		else {
			//
		}
		opengl_init(modern_context);
		wglSwapInterval =
			(wgl_swap_interval_ext*)wglGetProcAddress("wglSwapIntervalEXT");
		if (wglSwapInterval) {
			wglSwapInterval(1);
		}
	}
	else {
		assert(0);
	}
	ReleaseDC(window, hdc);




}

LRESULT CALLBACK
window_callback(HWND window,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	LRESULT result = 0;

	switch (message) {
	case WM_PAINT: {
		PAINTSTRUCT paint;
		HDC hdc = BeginPaint(window, &paint);
		EndPaint(window, &paint);
	}break;

	case WM_QUIT:
	case WM_DESTROY: {
		running = false;
	}break;

	case WM_COMMAND: {
		if (LOWORD(wParam) == 2) {
			running = false;
		}
	}break;

	default: {
		result = DefWindowProc(window, message, wParam, lParam);
	}break;
	}
	return result;
}

int WINAPI
WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{

	WNDCLASS window_class = { 0 };
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpfnWndProc = window_callback;
	window_class.hInstance = hInstance;
	window_class.lpszClassName = "Opengl Practice";

	RegisterClass(&window_class);

	HWND window = CreateWindowEx(0, window_class.lpszClassName, "Playing Around", WS_OVERLAPPED | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1744, 1119, 0, 0, hInstance, 0);

	//initilalized opengl, sets the current window_class to the opengl window and also compiles the shader codes in gl_config global variable
	win32_init_opengl(window);

	glUseProgram(gl_config.id);


	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	u32 VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// load and create a texture 
	// -------------------------
	unsigned int texture1, texture2;
	// texture 1
	// ---------
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);


	unsigned char* data = stbi_load("./pond.jpg", &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);


	//Texture 2

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	data = stbi_load("./house.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
	}
	stbi_image_free(data);

	glUniform1i(glGetUniformLocation(gl_config.id, "texture1"), 0);
	glUniform1i(glGetUniformLocation(gl_config.id, "texture2"), 1);

	running = true;



	while (running) {
		MSG msg;
		while (PeekMessage(&msg, window, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActivateTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActivateTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glm::mat4 transform = glm::mat4(1.0f);

		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));

		transform = glm::rotate(transform, (float)10.0f, glm::vec3(0.0f, 0.0f, 1.0f));


		glUseProgram(gl_config.id);


		u32 transform_loc = glGetUniformLocation(gl_config.id, "transform");

		glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));

		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		HDC hdc = GetDC(window);
		SwapBuffers(hdc);
		ReleaseDC(window, hdc);

		DwmFlush();
	}

}













