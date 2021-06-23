#include <cstdlib>
#include <cstdio>
#include "IsE_Hacker.hpp"

const double FrameRateMs = 0.050;
const int nCoockies = 20;
const int minCoockiesToHack = 30;

const int mimVelocity = 50;     //pixels per second
const int velocityRange = 200;

long long coockieCounter = 0;

unsigned char ROR (unsigned char a, unsigned char b)
{
    unsigned char c = a;
    for (unsigned char i = 0; i < b; i++)
        c = c >> 1 | c << 7;
    return c;
}

unsigned char ROL (unsigned char a, unsigned char b)
{
    unsigned char c = a;
    for (unsigned char i = 0; i < b; i++)
        c = c << 1 + c >> 7;

    return c;
}

unsigned char* ReadAndSolvePassword (const char* filename, const int firstBuffBegin, const int secondBuffBegin, const int thirdBuffbegin, const int BuffSize)
{
    FILE* comFile = fopen (filename, "r+");
    if (!comFile)
    {
        printf ("File not opened.\n");
        return nullptr;
    }

    unsigned char* first  = (unsigned char*) calloc (BuffSize + 1, sizeof(char));
    unsigned char* second = (unsigned char*) calloc (BuffSize + 1, sizeof(char));
    unsigned char* third  = (unsigned char*) calloc (BuffSize + 1, sizeof(char));

    fseek (comFile, firstBuffBegin, SEEK_SET);
    fread (first, sizeof(char), BuffSize, comFile);

    fseek (comFile, secondBuffBegin, SEEK_SET);
    fread (second, sizeof(char), BuffSize, comFile);

    fseek (comFile, thirdBuffbegin, SEEK_SET);
    fread (third, sizeof(char), BuffSize, comFile);

    for (int i = 0; i < 16; i++)
    {
        first[i+1]  = SolvePassword (first[i], third[i], second[i]);
        third[i+1] = CalcSymb (first[i], third[i], first[i+1]);
    }
    //printf ("\n");
    free (first);
    free (second);
    free (third);
    return first;
}

unsigned char SolvePassword (unsigned char previous, unsigned char passSymbPrevious, unsigned char passSymbCurrent)
{
    for (unsigned char i = 0; i < 255; i++)
    {   
        unsigned char current = CalcSymb (previous, passSymbPrevious, i); 
        if (current == passSymbCurrent)
        {
            printf("%c", i);
            return i;
        }
    }
    printf("bad password, try another hack\n");
    return '\0';
}

unsigned char CalcSymb (unsigned char ourSymb, unsigned char theirSymb, unsigned char current){
    
    ourSymb   -= theirSymb;
    theirSymb += 220;
    unsigned char temp = theirSymb;
    theirSymb = ROR (theirSymb, ourSymb);

    theirSymb -= temp;
    theirSymb += current;

    return theirSymb;
}

void crushCode (char* fileName, int weekAddress, int nNops){
    FILE* com = fopen (fileName, "r+");
    fseek (com, weekAddress, SEEK_SET);
    for (int i = 0; i < nNops; i++)
    fputc (144, com);
}

int launchCracker ()
{
     std :: srand(time(0));
    sf :: Texture background;

    sf :: Music music;
    if (!music.openFromFile("crMus.ogg"))
        return EXIT_FAILURE;

    sf:: Music hrust;
    if (!hrust.openFromFile("hrust.ogg"))
        return EXIT_FAILURE;

    if (!background.loadFromFile("background.png"))
        return EXIT_FAILURE;

    sf :: Vector2i pictureParams (background.getSize());
    sf :: RenderWindow window(sf::VideoMode(pictureParams.x, pictureParams.y), "SFML window");
    sf :: Sprite sprite (background);
    

    //Button buttonUp(100, 100, 50, 50, "mmm delicious", "button1.png");
    sf :: Texture button1;
    button1.loadFromFile ("void.png");
    sf :: Sprite butSprite (button1);
    sf :: Texture button2;
    button2.loadFromFile ("crack1.png");
    sf :: Sprite butSprite2 (button2);
    sf :: Texture button3;
    button3.loadFromFile ("crack2.png");
    sf :: Sprite butSprite3 (button3);

    Button buttonBrut (100,100, butSprite);

    music.play();
    music.setLoop(true);

    sf :: Clock timer;
    sf :: Time  currentTime;

    sf :: Clock MusicClock;

    InteractiveObject coockies[nCoockies];
    for (int i = 0; i < nCoockies; i++)
    {
        coockies[i].setMedia("hrust.ogg", butSprite);
        respawncoockie (coockies + i, window);
    }

    sf :: Time oldTime = MusicClock.getElapsedTime();
    
    sf :: Event event;
    while (window.isOpen())
    {    
        sf :: Time newTime = MusicClock.getElapsedTime();    
        
        while (window.pollEvent (event))
        {
            if (event.type == sf :: Event :: Closed)
                window.close();
            if (event.type == sf :: Event :: MouseButtonPressed)
            {
                if (CheckCoockieClicked (coockies, nCoockies, window, newTime - oldTime, event, butSprite2, butSprite3))
                    return 0;
            }
        }
        
        window.clear();
        window.draw(sprite);
        while (newTime.asSeconds() - oldTime.asSeconds() < FrameRateMs)
        {
            newTime = MusicClock.getElapsedTime(); 
        }

        CoockieSet (coockies, nCoockies, window, newTime - oldTime, event);
        MusicClock.restart();

        oldTime = MusicClock.getElapsedTime();
        window.display();
    }
    return 0;
    
}

void CoockieSet (InteractiveObject* buffer, const int SizeOfBuffer, sf :: RenderWindow& window, const sf :: Time& delta, sf :: Event& event)
{
    for (int i = SizeOfBuffer - 1; i >= 0; i--)
    {
        buffer[i].countOffset (delta);
        window.draw(buffer[i].getSprite());
    }
    for (int i = 0; i < SizeOfBuffer; i++)
    {
        if (buffer[i].getY() > window.getSize().y + 100)
        {
            respawncoockie (buffer + i, window);
        }            
    }
    window.display();
}

int CheckCoockieClicked (InteractiveObject* buffer, const int SizeOfBuffer,sf :: RenderWindow& window, const sf :: Time& delta, sf :: Event& event, sf :: Sprite& sprite1,  sf :: Sprite& sprite2)
{
    if (event.type == sf :: Event :: MouseButtonPressed)
    {
        if (event.type == sf :: Event :: Closed)
            window.close();
        for (int i = 0; i < SizeOfBuffer; i++)
            if (buffer[i].IsSelected(sf::Mouse::getPosition (window)))
            {
                buffer[i].playSound();
                coockieCounter++;
                printf ("%lld\n", coockieCounter);

                respawncoockie (buffer + i, window);

                if (coockieCounter > minCoockiesToHack)
                {
                    if (i == 0)
                    {
                        respawncoockie(buffer + 0, window);
                        ReadAndSolvePassword ("NO_HCK.COM", 102, 547, 119, 16);
                        return 2;
                    }
                    if (i == 1)
                    {
                        respawncoockie (buffer + 1, window);
                        crushCode ("NO_HCK.COM", 176, 5);
                        return 1;
                    }
                }
                if (coockieCounter == minCoockiesToHack)
                {

                    buffer[0].setMedia("hrust.ogg", sprite1);
                    buffer[1].setMedia("hrust.ogg", sprite2);
                }
                return 0;
            }
    }
    return 0;
}

void respawncoockie (InteractiveObject* coockie, const sf :: Window& window)
{
    unsigned int first = rand() % ((unsigned int)window.getSize().x - (unsigned int)coockie->getWidth());
    unsigned int second = mimVelocity + rand() % velocityRange;
    coockie->setPhysicsParametrs(first, -coockie->getHeight(), second);
}