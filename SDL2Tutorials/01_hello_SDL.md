# Hello SDL

如果你学过C++的基础，但是不想只是制作文本行形式的程序。为了能使用诸如图形，声音，键盘，摇杆等，你需要一套API来处理所有这些硬件特性，并把他们转成可以与C++交互的形式。

而这正是SDL做的事情。它可以处理Windows/Linux/Mac/Android/iOS 等等平台上的工具，并把他们包装成可以在SDL中编程的形式，然后就可以编译到它支持的所有平台上去。为了能使用它，你需要先安装它。

安装手册可以帮助你设置好SDL。可能最新的有些修改，那就查看最新的git上的文档。

SDL是个动态链接库，一个动态链接库包含三个部分：
1、头文件
2、静态库文件 （windows上是 .lib文件，类Unix平台上是 .a 文件）
3、动态库文件 （windows上是 .dll文件，类Unix平台上是 .so 文件）
你的编译器需要能定位到头文件，以便知道例如SDL_Init()和其他一些函数和结构体的定义。你可以在工程中配置头文件目录，或者把SDL的头文件和你工程中的其他头文件放在一起。

当你的所有的头文件完成编译之后，还需要把所有的编译结果链接在一起。为了让程序能正确地执行链接过程，编译器需要知道所有的函数，包括SDL提供的所有函数的地址。对于静态链接的库，地址存在于库文件内。库文件中保存有导入地址表，让你的程序可以在运行时定位到正确地函数地址。和头文件类似，你可以配置你的编译器，告诉他你的SDL库文件的保存位置，或者把SDL的库文件和你工程中的其他库文件放在一起。你还需要告诉链接器你要链接的库文件的名字。如果链接器提示说它找不到 -lSDL2 或者 SDL2.lib，那说明库文件没有在链接器查找库文件的目录内。如果链接器提示说有未定义的引用，那大概率是因为没有告诉链接器你要链接的库文件。

当你的程序完成编译和链接之后，运行的时候还需要动态加载这个库。动态链接的库文件在运行的时候需要能够导入需要的库文件。你的操作系统需要能够在程序运行的时候能够找到需要的库文件。你可以把库文件放在与可执行文件同样的目录下，也可以放到操作系统用来存放库文件的目录下，或者通过PATH环境变量告诉操作系统去从一个用户指定的目录下去查找库文件。

设置好SDL后，下一步是创建一个SDL2的窗口。

在Windows上设置SDL2开发环境

对windows开发者有个很重要的提示：
作为安装过程的一部分，需要把动态链接库文件放在你的程序能够在运行的时候链接到的位置，可以把dll文件和可执行文件放在一起，或者放在系统目录下，对32位的系统，放在C:\WINDOWS\SYSTEM32下，64位的系统放在C:\Windows\System64下。

把dll文件放在系统目录下的好处是：系统总是能找到库文件，因此能够在系统的任意位置编译和运行你的动态链接的程序，而不需要为你开发的每个应用都单独放一份dll文件。
但是在发布的时候，要消息不要弄坏用户的系统目录。目标用户可能会有多个程序，他们需要不同版本的SDL。你的dll文件应该和可执行文件放在一起。

1.第一步是下载SDL2的头文件和二进制文件。可以从SDL的github主页上找到。下载Visual C++ Development库：

github地址：https://github.com/libsdl-org/SDL/releases

这个页面上，SDL3 已经开始预发布了，但是我们这里要下载SDL2的Release版本：

打开这个压缩包，里面应该会有个目录叫 SDL2XXX （XXX是版本号之类的）。把这些都拷贝到一个存放你的Visual C++用的开发库的目录。对这套教程，我把他们都放在了目录 c:/vclib 下

然后在Visual C++中创建一个空的C++工程，添加一个CPP文件，并添加以下内容：
/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface( window );

			//Fill the surface white
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
			
			//Update the surface
			SDL_UpdateWindowSurface( window );
            
            //Hack to get window to stay up
            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
		}
	}

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}

然后在VC项目中，配置include目录，配置库文件的查找目录，添加链接依赖库文件SDL2.lib和SDL2main.lib 然后把库文件所在的目录添加到系统的PATH环境变量中，以便程序运行的时候能够找到正确地dll文件。最后重启visual C++，编译文件，应该就可以编译通过了。你会看到一个空的windows窗口。说明你的工程运行成功了。

如果运行过程中遇到问题，请参考：https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php


本手册介绍如何显示第一个SDL的图形窗口

现在你已经设置好SDL了，是时候制作一个能够在屏幕上渲染一个矩形的SDL图形应用的骨架了。

// 第一步是引用SDL和标准的输入输出
#include <SDL.h>
#include <stdio.h>

// 定制屏幕尺寸的常量

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// 包含SDL的头文件是为了能够使用SDL通过的函数，包含stdio.h是为了能够使用C的标准输入输出在终端输出错误。也可以用iostream，都行。

// 包含头文件之后，就声明渲染目标窗口的宽度和高度。

int main( int argc, char* args[] )
{
    //The window we'll be rendering to
    SDL_Window* window = NULL;
    
    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }

这是我们的main函数的开头，这里重要的一点是它的参数类型是一个int，和一个char*数组，并且返回值是int类型。其他类型main函数都可能会引起未定义的行为。SDL需要这种类型，以兼容其他多种平台。

然后我们声明一个SDL的窗口，我们稍后会创建它。然后声明一个SDL的图层。一个SDL的图层就是一个2D的图片。2D图片可以加载自一个文件，也可以是窗口内的一个图片。这里将是我们在屏幕的窗口中看到的图片。

声明了窗口和屏幕图层之后，我们初始化SDL。在调用任何SDL的其他函数之前，必须要先初始化SDL。因为我们关心的是使用SDL的视频子系统，我们只给他传递SDL_INIT_VIDEO标志。

如果发生了错误，SDL_Init会返回-1，当有错误发生时，我们希望把错误信息输出到控制台上，否则应用将只是闪一下，然后几秒之后就关闭了。


如果你从来没有使用过printf，它表示格式化输出。它会根据第一个参数的格式输出后续的参数数值。当有错误发生的时候，控制台会输出如下的错误信息："SDL could not initialize! SDL Errro: "，后面会跟着SDK_GetError返回的错误信息。%s指定了输出的格式。%是意思是字符串。SDL_GetError返回的是最近一次SDL函数产生的错误。

SDL_GetError是一个非常有用的函数。当需要知道到底是哪里出错的时候，SDL_GetError会告诉你SDL内部出错的信息。

    else
    {
        //Create window
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }

如果SDL初始化成功，我们将要使用SDL_CreateWindow来创建一个窗口。第一个参数设置窗口的名称。

后面两个参数定义窗口在x和y方向上的创建位置。因为我们并不关心窗口的创建位置，因此我们把x和y都设置为SDL_WINDOWPOS_UNDEFINED。

再往后两个参数，定义窗口的宽度和高度。最后一个窗口是创建标志。SDL_WINDOW_SHOWN会让窗口创建之后就显示出来。

如果有错误发生，SDL_CreateWindow会返回NULL。如果没有窗口，我们会把错误输出到控制台。

        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );

            //Fill the surface white
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            
            //Update the surface
            SDL_UpdateWindowSurface( window );

            //Hack to get window to stay up
            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
        }
    }

如果窗口创建成功，我们希望获得窗口的图层，以便于在上面花我们想画的内容。SDL_GetWindowSurface实现这个功能。

为了保持文章的简洁，我们只是用SDL_FillRect在窗口的图层上填充。这里还不需要太关心这个函数。这篇文章目前只专注于如何创建一个窗口并显示出来。

关于渲染，有个重要的事情需要知道的是，当你在图层上画了一些东西之后，还不一定能看到他们。当画完所有你想画的内容之后，你还需要更新一次窗口，才能把所有画过的东西显示出来。调用 SDL_UpdateWindowSurface 的作用就是这个。

如果我们做的事情只是创建窗口，填充，然后更新它，我们会只是看到窗口闪了一下，然后就关闭了。为了保持窗口一直显示，我们在最后放了一行代码来防止它自动关闭。通常，我们会调用SDL_Delay来延迟一段时间，但是MaxOS处理图形和输入的方法在我第一次写这篇文章的时候有些变化，但是我不想重构这篇文章来介绍这部分内容。我会在介绍事件的文章里详细解释如何正确地保持窗口开启，目前只要知道最后一行代码的作用就是如此就可以了。

你可能会觉得这样不太专业，但是如果你以后在游戏行业中工作后，你会很快发现，写一些临时解决问题的代码基本上是让游戏按时发布的唯一方法。

    // 释放窗口
    SDL_DestroyWindow( window );

    // 退出SDL
    SDL_Quit();

    return 0;
}

窗口显示完成之后，我们将会销毁窗口，然后释放它占用的内存。这也会同时销毁掉我们之前获取到的图层。在所有都清理干净之后，我们退出SDL，然后返回0值。


