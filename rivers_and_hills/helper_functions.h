#pragma once



struct ReadFileResult {
	u32 content_size;
	void* contents;
};

function ReadFileResult read_entire_file(char* file_name) {
	ReadFileResult result = {};
	HANDLE file_handle = CreateFileA(file_name, GENERIC_READ, FILE_SHARE_READ, 0,
		OPEN_EXISTING, 0, 0);
	if (file_handle != INVALID_HANDLE_VALUE) {
		u64 file_size;
		if (GetFileSizeEx(file_handle, (PLARGE_INTEGER)&file_size)) {
			result.contents =
				VirtualAlloc(0, file_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
			if (result.contents) {
				u32 bytes_read;
				if (ReadFile(file_handle, result.contents, file_size,
					(LPDWORD)&bytes_read, 0)) {
					result.content_size = file_size;
				}
				else {
					VirtualFree(result.contents, 0, MEM_RELEASE);
					result.contents = 0;
				}
			}
		}
		CloseHandle(file_handle);
	}
	return result;
}

function b32 strings_are_equal(char* a, char* b){
  b32 result = ( a == b);
  if(a && b){
    while(*a && *b &&(*a == *b)){
      ++a;
      ++b;
    }
    result = ((*a == 0) && (*b == 0));
  }
  return result;
}

function b32 strings_are_equal(u32 a_len, char* a, char* b){
  char* at = b;
  for(u32 i = 0; i < a_len; ++i, ++at){
    if((at == 0) || (a[i] != *at)){
      return false;
    }
  }
  b32 result = (*at == 0);
  return result;
}

function b32 is_eol(char c){
  b32 result = ((c == '\n') || (c == '\r'));
  return result;
}


function b32 is_whitespace(char c){
  b32 result = ((c == ' ') || (c == '\t') || (c == '\v') || (c == '\f') || is_eol(c));
  return result;
}




