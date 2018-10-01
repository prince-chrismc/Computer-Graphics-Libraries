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

#include "Interfaces.h"
#include <fstream>

Shader::IShader::IShader( const std::string& rel_path ) : m_Id( 0 ), m_Status( false )
{
   std::ifstream glsl_file( rel_path, std::ios::in );

   if( glsl_file.is_open() )
   {
      glsl_file >> m_Code;
      glsl_file.close();
      m_Status = true;
   }
   else
   {
      throw ShaderException( "Impossible to open " + rel_path + ". Are you in the right directory ?" );
   }
}

bool Shader::IProgram::Link( IShader* vertex, IShader* frag )
{
   if( vertex && frag )
      m_Status = AddShader( vertex ) && AddShader( frag );

   // Now lets link the program
   if( m_Status )
   {
      glLinkProgram( m_ProgramId );

      // Check for linking errors
      GLint success;
      glGetProgramiv( m_ProgramId, GL_LINK_STATUS, &success );

      if( !success )
      {
         m_Status = false;
         std::string log_buffer( 512, ' ' );
         glGetProgramInfoLog( m_ProgramId, 512, NULL, const_cast<char*>(log_buffer.data()) );

         throw ShaderException( "Program linking failed. Due to the following:\r\n" + log_buffer );
      }
   }

   return m_Status;
}

bool Shader::IProgram::AddShader( IShader * shader )
{
   if( ! (*shader)() ) throw ShaderException( "Unable to add shader which is not valid!" );

   glAttachShader( m_ProgramId, shader->GetId() );

   GLint attached_shaders;
   glGetProgramiv( m_ProgramId, GL_ATTACHED_SHADERS, &attached_shaders );
   if( attached_shaders == m_ShaderCounter + 1 )
   {
      m_ShaderCounter += 1;
      return true;
   }
   return false;
}
