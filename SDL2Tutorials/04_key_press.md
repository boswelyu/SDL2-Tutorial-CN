# 按键操作

点击X关闭窗口只是SDL能够处理的众多事件之一，另外一类在游戏中经常用到的事件是按键事件。本教程中，我们将实现根据不同的按键显示不同的图片的功能。

// 关于图层的按键常量定义
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

在代码的开始，我们先定义我们有的不同图层的枚举值。这里 KEY_PRESS_SURFACE_DEFAULT 将等于0， 后面一次加一。google enum。这里不啰嗦了。


开始编程时，一个坏习惯是使用任意的数字，而不是常量定义的符号。例如，直接使用1表示主菜单，2表示可选项等等，对小程序还好，但是对上千行的代码来说，最好用常量代替。

//初始化SDL并创建一个窗口
bool init();

//加载媒体
bool loadMedia();

//释放媒体，关闭SDL
void close();

//加载一张指定的图片
SDL_Surface* loadSurface( std::string path );

//渲染的目标窗口
SDL_Window* gWindow = NULL;
    
//窗口包含的图层
SDL_Surface* gScreenSurface = NULL;

//特定的按键对应的图层
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//当前显示的图层
SDL_Surface* gCurrentSurface = NULL;

在我们常用的函数之后，我们加了一个新的加载特定图层的函数，叫做loadSurface。一个通用的规则是，如果你要拷贝粘贴一段代码，那就是不对的。我们会把加载图像的代码抽象成一个函数，而不是到处复制粘贴他们。

这段程序里重要的部分是，我们声明了一个叫做gKeyPressSurfaces的数组来存放图层的指针，它包含了我们将会用到的所有的图像。根据玩家的按键，我们把gCurrentSurface设置为不同的图层。

SDL_Surface* loadSurface( std::string path )
{
    // 加载特定路径的图片
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    return loadedSurface;
}

loadSurface 用来加载图片，如果有错误发生，它会报告一个错误。和之前的功能一样，只是更好调试。

这个函数会分配内存，close函数里负责释放

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load default surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "04_key_presses/press.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
    {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    //Load up surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "04_key_presses/up.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
    {
        printf( "Failed to load up image!\n" );
        success = false;
    }

    //Load down surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "04_key_presses/down.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
    {
        printf( "Failed to load down image!\n" );
        success = false;
    }

    //Load left surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "04_key_presses/left.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
    {
        printf( "Failed to load left image!\n" );
        success = false;
    }

    //Load right surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "04_key_presses/right.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
    {
        printf( "Failed to load right image!\n" );
        success = false;
    }

    return success;
}

loadMedia函数里，我们加载所有要在屏幕上显示的图片

            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //Set default current surface
            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

            //While application is running
            while( !quit )
            {

 进入循环之前，先设置一幅默认的图像

                // 处理事件队列
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    // 玩家按键
                    else if( e.type == SDL_KEYDOWN )
                    {
                        //根据按键选择图层
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_UP:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                            break;

                            case SDLK_DOWN:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                            break;

                            case SDLK_LEFT:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                            break;

                            case SDLK_RIGHT:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                            break;

                            default:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                            break;
                        }
                    }
                }

这里是我们的事件循环。关闭窗口的处理和之前的教程是一样的，然后我们会处理SDL_KEYDOWN事件，这个事件会在按下键盘上任意一个键的时候产生。

在SDL事件内部，是SDL的按键事件，其中包含了按下哪个键的信息。

如你所见，这段代码根据按键设置不同的图层。要处理其他的按键，可以去查SDL的文档。

                //显示当前图片
                SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
            
                //更新图层
                SDL_UpdateWindowSurface( gWindow );

根据按键选择了图层之后，我们把他们渲染到屏幕上。