#pragma once

class Shader {
public:
	Shader(const char* vShaderFile, const char* fShaderFile);
	virtual ~Shader();

	void Bind() const;
	void UnBind() const;

	void SetUniform4x4(const char* name, float* entry);
	void SetUniform4(const char* name, float x, float y, float z, float w);
	void SetUniform3(const char* name, float x, float y, float z);

private:
	char* ReadFile(const char* filename);
	unsigned int CompileShader(const char* filename, int type);


public:
	unsigned int program;
	bool valid = true;
};
