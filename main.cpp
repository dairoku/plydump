// =============================================================================
//  main.cpp
//
//  MIT License
//
//  Copyright (c) 2019 Dairoku Sekiguchi
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
// =============================================================================
/*!
  \file     main.cpp
  \author   Dairoku Sekiguchi
  \version  1.0.0
  \date     2019/05/02
  \brief    
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int fd;
  FILE  *fp;
  struct stat stbuf;
  unsigned char *buf;
  char  *endPtr;

  if (argc < 2)
  {
    printf("Usage : plydump <file name>\n");
    return -1;
  }

  fd = ::open(argv[1], O_RDONLY);
  if (fd == -1)
  {
    printf("Failed : open()\n");
    return -1;
  }

  fp = ::fdopen(fd, "rb");
  if (fp == NULL)
  {
    printf("Failed : fdopen()\n");
    return -1;
  }

  if (::fstat(fd, &stbuf) == -1)
  {
    printf("Failed : fstat()\n");
    return -1;
  }
  size_t  fileSize = stbuf.st_size;
  
  buf = new unsigned char[fileSize];
  if (buf == NULL)
  {
    printf("Failed : buf == NULL\n");
    ::fclose(fp);
    return -1;
  }

  if (::fread(buf, sizeof(unsigned char), fileSize, fp) != fileSize)
  {
    printf("Failed : fread()\n");
    ::fclose(fp);
    return -1;
  }
  ::fclose(fp);

  endPtr = strstr((char *)buf, "end_header");
  if (endPtr == NULL)
  {
    printf("Can't find a PLY header\n");
    return -1;
  }
  endPtr += strlen("end_header");
  *endPtr = 0;

  // Print header (this is what we want to do :)
  printf("%s\n", buf);

  return 0;
}
