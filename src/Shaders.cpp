/*
MIT License

Copyright (c) 2017 Chris McArthur, prince.chrismc(at)gmail(dot)com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Shaders.h"

void Shader::Vertex::Compile()
{
   if (m_Status) // If the code was loaded by the base class
   {
      char const* glsl_buffer = m_Code.c_str();
      glShaderSource(m_Id, 1, &glsl_buffer, NULL);
      glCompileShader(m_Id);

      // Check for compile time errors
      GLint success;
      glGetShaderiv(m_Id, GL_COMPILE_STATUS, &success);
      if (!success)
      {
         m_Status = false;
         std::string log_buffer( 512, ' ' );
         glGetProgramInfoLog( m_Id, 512, NULL, const_cast<char*>( log_buffer.data() ) );

         throw ShaderException( "Vertex Shader Compilation failed. Due to the following:\r\n" + log_buffer );
      }
   }
}

void Shader::Fragment::Compile()
{
   if (m_Status) // If the code was loaded by the base class
   {
      char const* glsl_buffer = m_Code.c_str();
      glShaderSource(m_Id, 1, &glsl_buffer, NULL);
      glCompileShader(m_Id);

      // Check for compile time errors
      GLint success;
      glGetShaderiv(m_Id, GL_COMPILE_STATUS, &success);
      if (!success)
      {
         m_Status = false;
         std::string log_buffer( 512, ' ' );
         glGetProgramInfoLog( m_Id, 512, NULL, const_cast<char*>( log_buffer.data() ) );

         throw ShaderException( "Fragment Shader Compilation failed. Due to the following:\r\n" + log_buffer );
      }
   }
}
