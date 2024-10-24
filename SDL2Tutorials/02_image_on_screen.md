Getting an Image on the Screen

在屏幕上显示图片


现在你在屏幕上得到了一个窗口，现在我们在上面放一张图片。


本教程从现在开始，将会只覆盖源码的关键部分。要查看完整的程序，请下载完整的源码。

启动SDL并创建窗口
//Starts up SDL and creates window
bool init();

加载媒体
//Loads media
bool loadMedia();

释放媒体并关闭SDL
//Frees media and shuts down SDL
void close();

在上一篇教程中，我们把所有的代码都写在了main函数中。对小规模的程序这样做没有问题，但是对真正的程序（比如视频游戏），你应该把你的代码尽量模块化。就是说把代码组织成方便调试和复用的代码块。
In the first tutorial, we put everything in the main function. Since it was a small program we can get away with that, but in real programs (like video games) you want to have your code as modular as possible. This means you want your code to be in neat chunks that are each easy to debug and reuse.

这里，我们使用函数分别处理初始化，加载媒体，关闭SDL应用，我们在源文件的上部声明这几个函数。
Here it means we have functions to handle initialization, loading media, and closing down the SDL application. We declare these near the top of our source file.

我收到很多邮件问为什么 close 函数在C中会引起冲突，因为他不支持函数重载。这也是我为什么使用C++做这个教程的原因。所以这个函数叫做close不是bug。


// 这是我们要渲染的目标窗口
SDL_Window* gWindow = NULL;
    
// 这是窗口内包含的图层
SDL_Surface* gScreenSurface = NULL;

// 这是我们要显示的图片
SDL_Surface* gHelloWorld = NULL;

这里我们声明一些全局变量。在大型项目中，应该尽量避免使用全局变量。我们这里使用全局变量的原因是，希望保持我们的代码尽量简单，但是在大型项目中，全局变量会让事情变得更加复杂。考虑到我们是只有一个源文件的程序，还不需要太担心这个问题。

这里出现了一个新的数据类型，叫做SDL图层。一个SDL的图层，包含了一张图片的所有像素，和渲染它需要的所有其他信息。SDL图层使用软件渲染，也就是说它需要消耗CPU来渲染。也可以渲染一个硬件加速的图像，但是这要稍微困难一点，我们先学简单的。后面的教程会讲到如何用GPU加速。

Here's a new data type called an SDL Surface. An SDL surface is just an image data type that contains the pixels of an image along with all data needed to render it. SDL surfaces use software rendering which means it uses the CPU to render. It is possible to render hardware images but it's a bit more difficult so we're going to learn it the easy way first. In future tutorials we'll cover how to render GPU accelerated images.

这里我们要处理的图像是一副屏幕图像（显示在窗口中），图像会从一个文件中读出来。
The images we're going to be dealing with here are the screen image (what you see inside of the window) and the image we'll be loading from a file.

注意这里用了SDL Surface的指针，原因如下：
1）我们会用动态分配的内存来加载图像
2）用指针引用使用动态分配的内存的图像更好。
想象一下，你有一个游戏中的砖墙，它由多次渲染的相同砖块图像组成（就像《超级马里奥兄弟》里那样）。在内存中保存图像的很多副本是很浪费的，你可以只保留一份图像副本，然后反复渲染它多次。
Notice that these are pointers to SDL surfaces. The reason is that 1) we'll be dynamically allocating memory to load images and 2) it's better to reference an image by memory location. Imagine you had a game with a brick wall that consisted of the same brick image being rendered multiple times (like Super Mario Bros). It's wasteful to have dozens of copies of the image in memory when you can have one copy of the image and render it over and over again.

另外，一定要记得初始化你的指针，这里我们声明之后立即设置为了空指针。

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

如你所见，我们把SDL的初始化和创建窗口的代码放到了init函数中，然后用SDL_GetWindowSurface()获取了图层。

我们想在窗口内显示一副图片，要完成这个任务，我们需要获取到窗口内的图像。因此使用 SDL_GetWindowSurface() 来抓到窗口内包含的图层。

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load splash image
    gHelloWorld = SDL_LoadBMP( "02_getting_an_image_on_the_screen/hello_world.bmp" );
    if( gHelloWorld == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}

在loadMedia函数内，我们使用SDL_LoadBMP()函数加载我们的图片，这个函数需要传入bmp文件的路径，会返回加载后的图层。如果函数返回NULL，意思是加载失败，因此在终端上打印出SDL_GetError获得的错误信息。

这个代码里面，假设你有一个叫02_getting_an_image_on_the_screen的目录，里面有一张叫做hello_world.bmp的图片，并放在你的工作目录下。工作目录是你的应用当前正在操作的目录。通常，工作目录是可执行文件当前所在的目录，在如visual studio这样的IDE里面，工作目录是与vcxproj工程文件所在的目录。因此，如果你的应用找不到图像文件，需要确定目录是对的。

如果程序运行但是没法加载到图像，大概率是因为目录的问题。工作目录在不同的操作系统和不同的IDE上表现不一样，如果不行，我建议尝试把包含bmp图像的目录移动到不同的地方多尝试一下，直到程序可以运行。

void close()
{
    //Deallocate surface
    SDL_FreeSurface( gHelloWorld );
    gHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

在清理代码里，我们和以前一样销毁窗口，然后退出SDL，同时我们还要处理好我们之前加载出来的图层。我们使用SDL_FreeSurface()来销毁掉图层，不需要额外销毁窗口的图层，SDL_DestroyWindow会一起处理。

要养成销毁指针之后把他们置空的习惯。

为什么我们在程序结束之前，还要费功夫去销毁掉资源呢？他们不会在程序退出的时候自动清理掉吗？

这个问题的回答是：我不知道。这取决于你的操作系统，可能会也可能不会。欢迎来到C++的未定义行为的世界。一般的规则是，如果你能避免出现未定义行为，你就应该尽量避免。这是一个相当良性的未定义行为示例，但我见过工程师花费数天时间来排查由未定义行为引起的bug（顺便说一句，永远不要在构造函数中调用虚函数）。现在就开始认真对待未定义行为的习惯，因为你不会想在团队项目的紧迫的截止日期前去处理它。

int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Apply the image
            SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );

在我们的main函数中，我们初始化SDL然后加载一张图片。如果加载成功，我们用SDL_BlitSurface把加载到的图片渲染到屏幕上。

Blitting函数做的事情，是把源图层拷贝一份，复制到目标图层上。SDL_BlitSurface函数的第一个参数是源，第三个参数是目标，我们在后面的教程中再去讨论第二个和第四个参数。

如果只做这些，我们还是不能从屏幕上看到我们加载出来的图片，我们还需要再做一步：
            // 更新图层
            SDL_UpdateWindowSurface( gWindow );

在往屏幕上花完所有想在当前帧里显示的内容之后，还需要用SDL_UpdateWindowSurface刷新一次屏幕。当你向屏幕上画一些东西的时候，通常不是向你当前在屏幕上看到的图像上去画东西。默认情况下，当前的大多数渲染系统都是双缓冲的，两个缓冲区分别是前台缓冲和后台缓冲。

当你使用如SDL_BlitSurface之类的画图调用时，你其实是画在后台缓冲上，而当前在屏幕上看到的前台缓冲。这样做的原因是，大多数帧内，都需要同时画很多个物体。如果只有一个前台缓冲区，我们就会看到还没画完的帧。因此我们先把东西都画到后台缓冲区，然后一次性交换前后台，保证用户看到完整的一帧。

这也意味着，你不能在每个blit调用之后就调用SDL_UpdateWindowSurface，而是一帧内的所有内容都blits之后，再调用一次。

            // 保持窗口打开
            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}

现在我们把所有的东西都渲染到窗口上了，然后我们保持窗口打开不要消失。等待之后，关闭程序。