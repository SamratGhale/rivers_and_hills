#ifndef RIVERS_OPENGL

#include <gl/GL.h>
#pragma comment(lib, "Opengl32.lib")


//This is kind of default methods i use for opengl

#define GL_FRAMEBUFFER_SRGB                     0x8DB9
#define GL_SRGB8_ALPHA8                         0x8C43
#define GL_LINK_STATUS                          0x8B82
#define GL_SHADING_LANGUAGE_VERSION             0x8B8C

// NOTE: Windows-specific
#define WGL_CONTEXT_MAJOR_VERSION_ARB           0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB           0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB             0x2093
#define WGL_CONTEXT_FLAGS_ARB                   0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB            0x9126

#define WGL_CONTEXT_DEBUG_BIT_ARB               0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB  0x0002

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002

#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_MULTISAMPLE                    0x809D
#define GL_ARRAY_BUFFER                   0x8892
#define GL_STATIC_DRAW                    0x88E4
#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_RGBA                           0x1908
#define GL_BGRA                           0x80E1
#define GL_DYNAMIC_DRAW                   0x88E8


typedef size_t GLsizeiptr;
typedef u64 GLintptr;

typedef BOOL WINAPI wgl_swap_interval_ext(int interval);

global_variable wgl_swap_interval_ext* wglSwapInterval;

typedef HGLRC WINAPI wgl_create_context_attribs_arb(HDC hdc,
                                                    HGLRC hShareContext,
                                                    const int* attribList);
typedef void gl_attach_shader(GLuint program, GLuint shader);
typedef void gl_compile_shader(GLuint shader);
typedef GLuint gl_create_program(void);
typedef GLuint gl_create_shader(GLenum type);
typedef void gl_delete_program(GLuint program);
typedef void gl_link_program(GLuint program);
typedef char GLchar;
typedef void gl_shader_source(GLuint shader, GLsizei count,
                              const GLchar* const* string, const GLint* length);
typedef void gl_use_program(GLuint program);
typedef void gl_validate_program(GLuint program);
typedef void gl_get_programiv(GLuint program, GLenum pname, GLint* params);
typedef void gl_get_program_info_log(GLuint program, GLsizei bufSize,
                                     GLsizei* length, GLchar* infoLog);
typedef void gl_get_shader_info_log(GLuint shader, GLsizei bufSize,
                                    GLsizei* length, GLchar* infoLog);
typedef GLint gl_get_uniform_location(GLuint program, const GLchar* name);
typedef void gl_get_uniform_iv(GLuint program, GLint location, GLint* params);
typedef void gl_uniform_1i(GLint location, GLint v0);
typedef void gl_uniform_4f(GLint location, GLfloat v0, GLfloat v1,
                           GLfloat V2_F32, GLfloat v3);
typedef void gl_uniform_2i(GLint location, GLint v0, GLint v1);
typedef void gl_uniform_matrix_4fv(GLint location, GLsizei count,
                                   GLboolean transpose, const GLfloat* value);
typedef void gl_bind_vertex_array(GLuint array);
typedef void gl_gen_vertex_arrays(GLsizei n, GLuint* arrays);
typedef void gl_gen_buffers(GLsizei n, GLuint* buffers);
typedef void gl_bind_buffer(GLenum target, GLuint buffer);
typedef void gl_buffer_data(GLenum target, GLsizeiptr size, const void* data,
                            GLenum usage);
typedef void gl_vertex_attrib_pointer(GLuint index, GLint size, GLenum type,
                                      GLboolean normalized, GLsizei stride,
                                      const void* pointer);
typedef void gl_enable_vertex_attrib_array(GLuint index);
typedef void gl_draw_elements(GLenum mode, GLsizei count, GLenum type,
                              const void* indices);
typedef void gl_active_texture(GLenum texture);
typedef void gl_uniform_2f(GLint location, GLfloat v0, GLfloat v1);
typedef void gl_buffer_sub_data(GLenum target, GLintptr offset, GLsizeiptr size,
                                const void* data);

typedef void gl_generate_mipmap(GLenum target);

global_variable gl_attach_shader* glAttachShader;
global_variable gl_compile_shader* glCompileShader;
global_variable gl_create_program* glCreateProgram;
global_variable gl_create_shader* glCreateShader;
global_variable gl_delete_program* glDeleteProgram;
global_variable gl_link_program* glLinkProgram;
global_variable gl_shader_source* glShaderSource;
global_variable gl_use_program* glUseProgram;
global_variable gl_validate_program* glValidateProgram;
global_variable gl_get_programiv* glGetProgramiv;
global_variable gl_get_program_info_log* glGetProgramInfoLog;
global_variable gl_get_shader_info_log* glGetShaderInfoLog;
global_variable gl_get_uniform_location* glGetUniformLocation;
global_variable gl_get_uniform_iv* glGetUniformiv;
global_variable gl_uniform_1i* glUniform1i;
global_variable gl_uniform_4f* glUniform4f;
global_variable gl_uniform_2i* glUniform2i;
global_variable gl_uniform_matrix_4fv* glUniformMatrix4fv;
global_variable gl_bind_vertex_array* glBindVertexArray;
global_variable gl_gen_vertex_arrays* glGenVertexArrays;
global_variable gl_gen_buffers* glGenBuffers;
global_variable gl_bind_buffer* glBindBuffer;
global_variable gl_buffer_data* glBufferData;
global_variable gl_vertex_attrib_pointer* glVertexAttribPointer;
global_variable gl_enable_vertex_attrib_array* glEnableVertexAttribArray;
global_variable gl_active_texture* glActivateTexture;
global_variable gl_uniform_2f* glUniform2f;
global_variable gl_buffer_sub_data* glBufferSubData;
global_variable gl_generate_mipmap* glGenerateMipmap;

//End of opengl default definations 

struct OpenglContext {
  u32 tex_handle;  // This will be uninitilized for tile
  u32 vbo;
  u32 vao;
  u32 ebo;
};


struct OpenglInfo {
  b32 modern_context;
  b32 GL_EXT_texture_sRGB;
  b32 GL_EXT_framebuffer_sRGB;
  b32 GL_ARB_framebuffer_object;

  char* vendor;
  char* renderer;
  char* version;
  char* shading_version;
  char* extensions;
};

struct OpenglConfig {
  GLuint id;
  GLuint default_internal_text_format;
};

global_variable OpenglConfig gl_config;

function OpenglInfo opengl_get_info(b32 modern_context){
  OpenglInfo result = {};
  result.modern_context = modern_context;
  result.vendor   = (char*)glGetString(GL_VENDOR);
  result.renderer = (char*)glGetString(GL_RENDERER);
  result.version  = (char*)glGetString(GL_VERSION);
  if(result.modern_context){
    result.shading_version = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
  }else{
    result.shading_version = "(none)";
  }
  result.extensions = (char*)glGetString(GL_EXTENSIONS);

  char* at = result.extensions;
  while(*at){
    while(is_whitespace(*at)) {++at;}
    char* end = at;
    //NOTE(samrat) Chopping up the string
    while(*end && !is_whitespace(*end)){++end;}
    u32 count = end - at;

    if(0){}
    else if(strings_are_equal(count, at, "GL_EXT_texture_sRGB")){
      result.GL_EXT_texture_sRGB=true;
    }else if(strings_are_equal(count, at, "GL_EXT_framebuffer_sRGB")){
      result.GL_EXT_framebuffer_sRGB=true;
    }
    at = end;
  }
  return result;
}


function GLuint opengl_create_program(char* vertex_code, char* fragment_code) {
  GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
  GLchar* vertex_shader_code[] = {
    vertex_code
  };
  glShaderSource(vertex_shader_id, array_count(vertex_shader_code), vertex_shader_code, 0);
  glCompileShader(vertex_shader_id);


  GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
  GLchar* fragment_shader_code[] = {
    fragment_code
  };
  glShaderSource(fragment_shader_id, array_count(fragment_shader_code), fragment_shader_code, 0);
  glCompileShader(fragment_shader_id);

  GLuint program_id = glCreateProgram();
  glAttachShader(program_id, vertex_shader_id);
  glAttachShader(program_id, fragment_shader_id);
  glLinkProgram(program_id);
  glValidateProgram(program_id);

  GLint linked = 0;
  glGetProgramiv(program_id, GL_LINK_STATUS, &linked);
  if(!linked){
    GLsizei ignored;
    char vertex_errors[4096];
    char fragment_errors[4096];
    char program_errors[4096];
    glGetShaderInfoLog(vertex_shader_id, sizeof(vertex_errors), &ignored, vertex_errors);
    glGetShaderInfoLog(fragment_shader_id, sizeof(fragment_errors), &ignored, fragment_errors);
    glGetProgramInfoLog(program_id, sizeof(program_errors), &ignored, program_errors);
    assert(0);
  }
  return program_id;
}

function OpenglInfo opengl_init(b32 modern_context) {

  OpenglInfo info = opengl_get_info(modern_context);
  gl_config.default_internal_text_format = GL_RGBA8;
  if(info.GL_EXT_texture_sRGB){
    gl_config.default_internal_text_format = GL_SRGB8_ALPHA8;
  }
  if(info.GL_EXT_framebuffer_sRGB){
    glEnable(GL_FRAMEBUFFER_SRGB);
  }

  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);

  char* vertex_code = (char* )read_entire_file("./vert.glsl").contents;
  char* fragment_code = (char*)read_entire_file("./frag.glsl").contents;

  //might need the header code later
  gl_config.id = opengl_create_program(vertex_code, fragment_code);

  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glLineWidth(1);

  return info;

}




#define RIVERS_OPENGL
#endif

