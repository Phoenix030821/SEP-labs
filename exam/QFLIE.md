QFile类我我们提供了操作文件的常用功能。它是一种io设备，可以用来读写文本文件和二进制文件，也可以用来读写Qt的资源文件。QFile类可以单独使用，该类本身提供了read/write函数，但更方便的方式是，将QFile和QTextStream或QDataStream一起使用。

一般情况下，使用QFile创建对象时，就会把要操作的文件名传递给它。但该类也提供了一个setFileName() 方法，允许我们在任何时候为QFile对象设置要操作的文件名。但是，QFile 只支持"/"，不支持"\"。

在构造QFile的对象后，我们可以使用exists() 判断文件是否存在，使用remove() 删除一个文件。在进行实际的内容读写前，需调用open（）打开文件，读写结束后，要调用close()关闭文件，也可以写调用一下flush()，冲刷缓冲区。就向我们刚才说的，我们一般使用QDataStream或QTextStream 读写文件，但我们也可以使用QFile继承自QIODevice的函数，如read()、readLine()、readAll()、write()等。除了读写函数外，我们还能使用size() 函数获得文件的大小；使用pos() 或 seek() 函数获取及设置文件读写的位置；使用atEnd() 函数判断是否到达了文件结尾。

直接使用QFile读写文件

 

```kotlin
  QFile file("in.txt");



      if (!file.open(QIODevice::ReadOnly | QIODevice::Text))



          return;



 



      while (!file.atEnd()) {



          QByteArray line = file.readLine();



          process_line(line);



      }
```


在此，我们将QIODevice::Text传给了open()函数，该标志是用来告诉Qt将文件中的换行符由"\r\n"，转换成"\n"。因为，默认情况下，QFile把文件当做二进制进行读写，不会进行任何的字节转换。
使用流读取文件:

 

   

```java
QFile file("in.txt");



      if (!file.open(QIODevice::ReadOnly | QIODevice::Text))



          return;



 



      QTextStream in(&file);



      while (!in.atEnd()) {



          QString line = in.readLine();



          process_line(line);



      }
```


QTextStream会把存储在磁盘上的8bit数据转换为16bit的Unicode 字符串QString。默认情况下，QTextStream假定文件使用的是用户系统的本地8bit编码。我们也可以使用QTextStream::setCodec() 函数还改变这种行为。
当使用QFile，QFileInfo和QDir类去操作文件系统时，你可以使用Unicode编码的文件名。在Unix平台上，这些文件名会被转换成8-bit编码。但如果你想使用标准c++ API或者平台特定的API去访问文件，那么你可以使用encodeName() 和 decodeName() 函数在Unicode文件名和8-bit文件名之间进行转换。

在Unix平台下，存在一些特殊的系统文件，例如/proc目录下，对这个文件调用size() 总是返回0，然而，你还是能够从此类文件中读取到数据；这些数据是为了相应你的read() 函数而间接产生出来的。但是，在这种情况下，你不能使用atEnd() 来判断是否还有数据可读（因为atEnd() 对于大小为0的文件返回true）。相反，你应该调用readAll()，或 反复调用read()、readLine()知道没有数据可读为止。如下代码所示，我们使用QTextStream一行一行的读取/proc/modules文件：


  

```java
  QFile file("/proc/modules");



      if (!file.open(QIODevice::ReadOnly | QIODevice::Text))



          return;



 



      QTextStream in(&file);



      QString line = in.readLine();



      while (!line.isNull()) {



          process_line(line);



          line = in.readLine();



      }
```


其实，除了上面使用的QFile从QIODevice继承的open() 函数外，QFile本身也为我们提供了两个open() 函数：

bool open(FILE *fh, OpenMode mode, FileHandleFlags handleFlags = DontCloseHandle)
bool open(int fd, OpenMode mode, FileHandleFlags handleFlags = DontCloseHandle)

第一个open() 会按一定的模式打开一个现存的文件指针。同时，可以再指定额外的标志。如下代码所示：

 

```cpp
  #include <stdio.h>



 



  void printError(const char* msg)



  {



      QFile file;



      file.open(stderr, QIODevice::WriteOnly);



      file.write(msg, qstrlen(msg));        // write to stderr



      file.close();



  }
```


当一个QFile已这种方式打开时，那么后续的close() 函数的作用会受到AutoCloseHandle标志的影响。如果指定了该标志，并且这个open() 函数调用成功了，那么后续再QFile对象上调用close() 会关闭底层文件句柄。否则，若没指定这个标志，close（）函数不会真正的关闭底层文件句柄，而只是冲刷 了一下缓冲区。如下测试代码所示：

 

```cpp
#include <QCoreApplication>



#include <QFile>



#include <cstdio>



 



int main(int argc, char *argv[])



{



    QCoreApplication a(argc, argv);



 



    FILE *pf = fopen("test.txt", "wb");



    if(pf == nullptr)



        return 0;



    QFile file;



    file.open(pf, QIODevice::WriteOnly); //1



    //file.open(pf, QIODevice::WriteOnly, QFileDevice::AutoCloseHandle); //2



    file.write("hello");



    file.close();



    fwrite("world", strlen("world"), 1, pf);



 



    return a.exec();



}
```


当我们使用 1处的方式打开文件指针，即不指定AutoCloseHandle标志，则close() 函数后的“world”是可以继续被写入文件的；若使用2处的方式打开文件指针，则“world”并不会再被写入文件，因为底层文件已关闭。

第二个open() 函数与此类似，只不过其是按一定模式打开一个现存的文件描述符。AutoCloseHandle标志也会影响后续的close（）函数。同时，如果QFile已这种方式打开，那么它会被自动地设置为raw mode，这意味着文件的输入、输出函数的执行会变慢。如果你遇到了性能问题，你应该尝试使用其他的打开函数。

至于其他的成员函数，比如文件的删除、重命名，文件访问权限的设置，Qt的帮助文档已讲的很清除，大家可以在使用时随时查看即可。