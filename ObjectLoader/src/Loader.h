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

#pragma once

#include "File.h"
#include "Model.h"

namespace Obj
{
   class Loader
   {
   public:
      Loader(const char* path) : m_File(path) { if(m_File) { ExtractData(); SortCoords(); } }
      ~Loader() = default;

      Model GetModel() { return m_Model; }

   private:
      File m_File;
      Model m_Model;

      std::vector<std::string> m_Indicies;

      std::vector<unsigned int> m_VerticeIndicies;
      std::vector<unsigned int> m_TextureIndicies;
      std::vector<unsigned int> m_NormalsIndicies;

      enum class Offset : size_t
      {
         VERTICE = 2,
         NORMAL = 3,
         TEXTURE = 3,
         INDEX = 2,
      };

      void ExtractData();
         void ExtractVertice(const std::string & line);
         void ExtractNormal(const std::string & line);
         void ExtractTexture(const std::string & line);
         void ExtractIndexing();
      void SortCoords();
   };
}
