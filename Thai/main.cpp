#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <SDL_mixer.h> 
#define f first
#define s second
using namespace std;


bool inMainMenu = true;
clock_t lastShootTime = clock();
bool quit = false;
bool levelCompleted = false; 
bool gamePaused = false;
bool gameOver = false;
bool aboutbutton = false;
int selectedCharacter = -1;
int selectedCharacterIndex = 0;
bool optionbutton = false;

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
SDL_Surface* backgroundSurface = NULL;
SDL_Texture* backgroundTexture = NULL;
SDL_Surface* characterSurface = NULL;
SDL_Texture* characterTexture = NULL;
SDL_Texture* bullet = NULL;     
SDL_Texture* threatObject = NULL;
SDL_Texture* live = NULL;
SDL_Texture* explosionTexture = NULL;
SDL_Texture* bulletTexture = NULL;   
SDL_Texture* mainMenu = NULL;
SDL_Texture* play = NULL;
SDL_Texture* about = NULL;
SDL_Texture* ending = NULL;
SDL_Texture* bossgame = NULL;
SDL_Texture* greenbullet = NULL;
SDL_Texture* bkgrover = NULL;
SDL_Texture* pauseG = NULL;
SDL_Texture* ship1 = NULL;
SDL_Texture* ship2 = NULL;
SDL_Texture* ship3 = NULL;
SDL_Texture* ship4 = NULL;
SDL_Texture* ship5 = NULL;          
SDL_Texture* option = NULL;
SDL_Texture* khungoption = NULL;

SDL_Rect characterRect = { 0, 0, 100, 100 };
SDL_Rect mainMenu_rect;
SDL_Rect play_Rect;
SDL_Rect about_Rect;
SDL_Rect ending_rect;
SDL_Rect bkgrover_rect;
SDL_Rect pauseG_rect;
SDL_Rect ship1_rect;
SDL_Rect ship2_rect;
SDL_Rect ship3_rect;
SDL_Rect ship4_rect;
SDL_Rect ship5_rect;
SDL_Rect option_rect;
SDL_Rect khungoption_rect;

SDL_Color color = { 255, 255, 255}; 
TTF_Font* font;
int health = 3;
int score = 9;
int trungdan = 0;
int traitim = 3;
SDL_Rect healthRect = { 10, 10, 100, 30 }; 

vector<pair<int, int>> toadodan;
//vector<SDL_Texture*> characterTextures;

struct ThreatObject {
    int x, y;
    
    
    int speed;
    char direction;
    clock_t lastShootTime;
    double timeBetweenShots;
    ThreatObject(int _x, int _y, int _speed, char _direction) : x(_x), y(_y), speed(_speed), direction(_direction), lastShootTime(clock()) {}
};

struct Bullet {
    int x, y;  
    double speed; 
    SDL_Texture* texture; 

    Bullet(int _x, int _y, double _speed, SDL_Texture* _texture) : x(_x), y(_y), speed(_speed), texture(_texture) {}
};
vector<Bullet> threatBullets; 
struct Explosion {
    SDL_Rect rect; 
    int frames; 
};

vector<Explosion> explosions;  

vector<ThreatObject> threatObjects;  

void inbackground();
void innhanvat(int x, int y);
void indan();
void inThreatObject();
void moveThreatObjects();
bool checkCollision(SDL_Rect a, SDL_Rect);
void shootThreatObjects();
void checkCharacterCollision();
void decreaseHealth();
void drawHealth();
void createMainMenu(SDL_Renderer* renderer);
void createLevel(int level);
void renderText(const std::string& text, int x, int y, int fontSize, SDL_Renderer* renderer);
void gameover(); 
void endinggame(SDL_Renderer* renderer);
void soundEffect();
void gameoverover();
void gameabout1();
void gameabout2();
void overEndingGame(SDL_Renderer* renderer);
void pressPauseGame(SDL_Renderer* renderer);
void gameabout3();
void selectCharacterImage(int index);
void showCharacterSelectionMenu();
void handleCharacterSelectionEvent(SDL_Event& e);

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return -1;
    }
    TTF_Init();
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 680, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface* imagebullet = IMG_Load("bullet01.png");   
    SDL_Surface* threatObjectSurface = IMG_Load("threatObject.png");
    SDL_Surface* explosionSurface = IMG_Load("no.png");     
    SDL_Surface* liveSurface = IMG_Load("heart.png");
    SDL_Surface* mainMenuSurface = IMG_Load("d2t1.jpg");
    SDL_Surface* playSurface = IMG_Load("play.png");
    SDL_Surface* aboutSurface = IMG_Load("about.png");
    SDL_Surface* endingSurface = IMG_Load("testbk.jpg");
    SDL_Surface* bossgameSurface = IMG_Load("threatObject.png");
    SDL_Surface* greenbulletSurface = IMG_Load("enemybullet.png");
    SDL_Surface* bkgroverSurface = IMG_Load("bkgrgover.jpg");
    SDL_Surface* pauseGSurface = IMG_Load("d2t3.jpg");
    SDL_Surface* ship1S = IMG_Load("ship1.png");
    SDL_Surface* ship2S = IMG_Load("ship2.png");
    SDL_Surface* ship3S = IMG_Load("ship3.png");
    SDL_Surface* ship4S = IMG_Load("ship4.png");
    SDL_Surface* ship5S = IMG_Load("ship5.png");
    SDL_Surface* optionS = IMG_Load("option.png");
    SDL_Surface* khungoptionS = IMG_Load("khungoption.png");
    backgroundSurface = IMG_Load("background.jpg");
    
    bullet = SDL_CreateTextureFromSurface(renderer, imagebullet);   
    threatObject = SDL_CreateTextureFromSurface(renderer, threatObjectSurface);
    explosionTexture = SDL_CreateTextureFromSurface(renderer, explosionSurface);
    live = SDL_CreateTextureFromSurface(renderer, liveSurface);
    mainMenu = SDL_CreateTextureFromSurface(renderer, mainMenuSurface);
    play = SDL_CreateTextureFromSurface(renderer, playSurface);
    about = SDL_CreateTextureFromSurface(renderer, aboutSurface);
    ending = SDL_CreateTextureFromSurface(renderer, endingSurface);
    bossgame = SDL_CreateTextureFromSurface(renderer, bossgameSurface);
    greenbullet = SDL_CreateTextureFromSurface(renderer, greenbulletSurface);
    bkgrover = SDL_CreateTextureFromSurface(renderer, bkgroverSurface);
    pauseG = SDL_CreateTextureFromSurface(renderer, pauseGSurface);
    ship1 = SDL_CreateTextureFromSurface(renderer, ship1S);
    ship2 = SDL_CreateTextureFromSurface(renderer, ship2S);
    ship3 = SDL_CreateTextureFromSurface(renderer, ship3S);
    ship4 = SDL_CreateTextureFromSurface(renderer, ship4S);
    ship5 = SDL_CreateTextureFromSurface(renderer, ship5S);
    option = SDL_CreateTextureFromSurface(renderer, optionS);
    khungoption = SDL_CreateTextureFromSurface(renderer, khungoptionS);

    font = TTF_OpenFont("Jersey25-Regular.ttf", 28);
    SDL_FreeSurface(explosionSurface);


   
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    characterSurface = IMG_Load("spaceship.png");
   
    SDL_SetColorKey(characterSurface, SDL_TRUE, SDL_MapRGB(characterSurface->format, 255, 255, 255));
    characterTexture = SDL_CreateTextureFromSurface(renderer, characterSurface);
    SDL_FreeSurface(characterSurface);

    SDL_Event e;
    int mouseX = 0, mouseY = 0;   

   

    for (int i = 0; i < 4; ++i) {
        int x = rand() % (1280 - 50);  
       int y = rand() % (100 - 50);   
       int speed = 0;
       char direction = (rand() % 2 == 0) ? 'L' : 'R'; 
       threatObjects.push_back(ThreatObject{ x, y, speed, direction });
    }
    int level = 1;
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }

    
    Mix_Music* backgroundMusic = Mix_LoadMUS("war-drums-173853.mp3");
    if (backgroundMusic == NULL) {
        printf("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }

    
    Mix_PlayMusic(backgroundMusic, -1);
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION) {

                mouseX = e.button.x;
                mouseY = e.button.y;
                if (inMainMenu && e.type == SDL_MOUSEBUTTONDOWN) {

                    if (mouseX >= play_Rect.x && mouseX <= play_Rect.x + play_Rect.w &&
                        mouseY >= play_Rect.y && mouseY <= play_Rect.y + play_Rect.h) {
                        inMainMenu = false;
                    }
                    else if (mouseX >= about_Rect.x && mouseX <= about_Rect.x + about_Rect.w &&
                        mouseY >= about_Rect.y && mouseY <= about_Rect.y + about_Rect.h) {
                        aboutbutton = true;
                        //inMainMenu = false;
                    }
                    else if (mouseX >= option_rect.x && mouseX <= option_rect.x + option_rect.w &&
                        mouseY >= option_rect.y && mouseY <= option_rect.y + option_rect.h) {
                        optionbutton = true;
                        //inMainMenu = false;
                    }
                }

                else {

                    innhanvat(mouseX, mouseY);
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        toadodan.push_back({ mouseX - 25,mouseY - 50 });

                    }
                }
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE) {
                    // Đảo ngược trạng thái pause/resume khi nhấn phím SPACE
                    gamePaused = !gamePaused;
                }
            }
        }

        if (!gamePaused) {
            if (inMainMenu) {

                createMainMenu(renderer);
                SDL_RenderCopy(renderer, mainMenu, NULL, &mainMenu_rect);
                SDL_RenderCopy(renderer, play, NULL, &play_Rect);
                SDL_RenderCopy(renderer, about, NULL, &about_Rect);
                SDL_RenderCopy(renderer, option, NULL, &option_rect);
                if (aboutbutton && inMainMenu)
                {
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, play, NULL, &play_Rect);
                    SDL_RenderCopy(renderer, option, NULL, &option_rect);
                    gameabout1();
                    gameabout2();
                    gameabout3();
                }
                if (optionbutton && inMainMenu)
                {
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, play, NULL, &play_Rect);
                    SDL_RenderCopy(renderer, about, NULL, &about_Rect);
                    showCharacterSelectionMenu();
                    handleCharacterSelectionEvent(e);
                }
            }

            else {

                inbackground();
                drawHealth();
                innhanvat(mouseX, mouseY);
                inThreatObject();
                moveThreatObjects();
                indan();
                shootThreatObjects();
                checkCharacterCollision();

                if (levelCompleted) {

                    level++;
                    createLevel(level);

                    levelCompleted = false;

                }

                if (level > 6)
                {
                    endinggame(renderer);
                    gameover();

                }
                if (trungdan == 3) {
                    SDL_RenderClear(renderer);
                    overEndingGame(renderer);
                    gameover();
                    gameoverover();

                    SDL_Delay(200);

                }
            }

            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);
            SDL_Delay(10);
        }
    }
    if (gamePaused) {
        // Hiển thị thông báo pause
         SDL_RenderClear(renderer);
         pressPauseGame( renderer);
    }

    Mix_FreeMusic(backgroundMusic);
    Mix_CloseAudio();


    SDL_Quit();
    return 0;
}

void inbackground() {
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    for (int i = 0; i < explosions.size(); ++i) {
        SDL_RenderCopy(renderer, explosionTexture, NULL, &explosions[i].rect);
    }

}

void innhanvat(int x, int y) {
    if (!inMainMenu) { // Chỉ in nhân vật khi không ở trong Main Menu
        characterRect.x = x - (characterRect.w / 2);
        characterRect.y = y - (characterRect.h / 2);
        if (selectedCharacter == -1) {
        SDL_RenderCopy(renderer, characterTexture, NULL, &characterRect);
        }
        else if (selectedCharacter==1) {
            SDL_RenderCopy(renderer, ship1, NULL, &characterRect);
        }
        else if (selectedCharacter==2) {
            SDL_RenderCopy(renderer, ship2, NULL, &characterRect);
        }
        else if (selectedCharacter==3) {
            SDL_RenderCopy(renderer,ship3,NULL,&characterRect);
        }
        else if (selectedCharacter==4) {
            SDL_RenderCopy(renderer, ship4, NULL, &characterRect);
        }
        else if (selectedCharacter==5) {
            SDL_RenderCopy(renderer, ship5, NULL, &characterRect);
        }
        
    }
}

void indan() {
    SDL_Rect bulletRect;
    bulletRect.w = 30;  
    bulletRect.h = 60;  

    for (int i = 0; i < toadodan.size(); ++i) {
        bulletRect.x = toadodan[i].f;
        bulletRect.y = toadodan[i].s;

        SDL_RenderCopy(renderer, bullet, NULL, &bulletRect);
        toadodan[i].s -= 4;   

        
        for (int j = 0; j < threatObjects.size(); ++j) {
            SDL_Rect threatRect = { threatObjects[j].x, threatObjects[j].y, 50, 50 };
            if (checkCollision(bulletRect, threatRect)) {
                
                toadodan.erase(toadodan.begin() + i);
                threatObjects.erase(threatObjects.begin() + j);
                --i;   
                break;  

                
            }
        }
    }
    
    for (int j = 0; j < threatObjects.size(); ++j) {
        SDL_Rect threatRect = { threatObjects[j].x, threatObjects[j].y, 50, 50 };
        for (int i = 0; i < toadodan.size(); ++i) {
            SDL_Rect bulletRect = { toadodan[i].f, toadodan[i].s, 50, 50 };
            if (checkCollision(bulletRect, threatRect)) {
                
                Explosion explosion;
                explosion.rect.x = threatRect.x;  
                explosion.rect.y = threatRect.y;
                explosion.rect.w = threatRect.w;  
                explosion.rect.h = threatRect.h;
                explosion.frames = 10;            
                explosions.push_back(explosion);  
                score += 10;
                soundEffect();
                break;
            }
           
        }
    }
   
}

void inThreatObject()
{
    for (auto& obj : threatObjects) 
    {
        SDL_Rect toado = { obj.x, obj.y, 60, 60 }; 
        SDL_RenderCopy(renderer, threatObject, NULL, &toado); 
    }
}

void moveThreatObjects() {
    for (auto& obj : threatObjects) {
        obj.y += obj.speed;   

        
        if (obj.y >= 680) {
            decreaseHealth();
            obj.y = -50;        
            obj.x = rand() % (1280 - 50);   
            traitim--;
        }
        
    }
   
    for (int i = 0; i < explosions.size(); ++i) {
        explosions[i].frames--;         
        if (explosions[i].frames <= 0) {
            explosions.erase(explosions.begin() + i);  
            i--;       
        }
    }
    
}

bool checkCollision(SDL_Rect a, SDL_Rect b) {
    if (a.x + a.w <= b.x) return false;
    if (a.x >= b.x + b.w) return false;
    if (a.y + a.h <= b.y) return false;
    if (a.y >= b.y + b.h) return false;
    return true;
}

void shootThreatObjects() {
    bool bulletShot = false; 
    for (auto& obj : threatObjects) {
        double timeSinceLastShoot = (double)(clock() - obj.lastShootTime) /  CLOCKS_PER_SEC ;
        if (timeSinceLastShoot >=   obj.timeBetweenShots&& ! bulletShot) {   
            

            int bulletX = obj.x + 25;  
            int bulletY = obj.y + 25;
            threatBullets.push_back(Bullet{ bulletX, bulletY, 2, bullet }); 
            obj.lastShootTime = clock();    
           
            obj.timeBetweenShots = (rand() % 7 + 5 ); 
        }
    }

   
    SDL_Rect bulletRect;
    bulletRect.w = 25;   
    bulletRect.h = 50; 
        
    for (auto& bullet : threatBullets) {
        bulletRect.x = bullet.x;
        bulletRect.y = bullet.y;

        SDL_RenderCopy(renderer, greenbullet, NULL, &bulletRect);
        bullet.y += bullet.speed;      

       
        SDL_Rect characterCollisionRect = { characterRect.x, characterRect.y, characterRect.w, characterRect.h };
        if (checkCollision(bulletRect, characterCollisionRect)) {
            decreaseHealth(); 
        }
    }
}

void checkCharacterCollision() {
    SDL_Rect characterCollisionRect = { characterRect.x, characterRect.y, characterRect.w, characterRect.h };

    for (int i = 0; i < threatBullets.size(); ++i) {
        SDL_Rect bulletRect = { threatBullets[i].x, threatBullets[i].y, 25, 25 };

        if (checkCollision(bulletRect, characterCollisionRect)) {
            
            Explosion explosion;
            explosion.rect.x = threatBullets[i].x;  
            explosion.rect.y = threatBullets[i].y+30;
            explosion.rect.w = 80;  
            explosion.rect.h = 80;
            explosion.frames = 10;
            explosions.push_back(explosion);
            decreaseHealth();
            trungdan++;
            traitim--;
            threatBullets.erase(threatBullets.begin() + i);
            --i; 
        }
    }
    
    if (threatObjects.empty()) {
        levelCompleted = true; 
    }
}

void decreaseHealth() {
    health--; 
}

void drawHealth() {
    int heartWidth = 30; // Chiều rộng của trái tim
    int heartHeight = 30; // Chiều cao của trái tim
    int heartSpacing = 5; // Khoảng cách giữa các trái tim
    int initialX = 5; // Vị trí ban đầu của trái tim đầu tiên
    int y = 5; // Vị trí theo chiều dọc của các trái tim

    for (int i = 0; i < traitim; ++i) {
        SDL_Rect heartRect = { initialX + (heartWidth + heartSpacing) * i, y, heartWidth, heartHeight };
        SDL_RenderCopy(renderer, live, NULL, &heartRect); // Vẽ trái tim tại vị trí tương ứng
    }
}

void createMainMenu(SDL_Renderer* renderer) {
    
    mainMenu_rect.x = 0;
    mainMenu_rect.y = 0;
    mainMenu_rect.w = 1280;
    mainMenu_rect.h = 680;

   
    play_Rect.x = 1000;
    play_Rect.y = 200;
    play_Rect.w = 200;
    play_Rect.h = 50;


    about_Rect.x = 1000;
    about_Rect.y = 300;
    about_Rect.w = 200;
    about_Rect.h = 50;

    
    option_rect.x = 1000;
    option_rect.y = 400;
    option_rect.w = 200;
    option_rect.h = 200;

    SDL_RenderCopy(renderer, mainMenu, NULL, &mainMenu_rect);
    SDL_RenderCopy(renderer, play, NULL, &play_Rect);
    SDL_RenderCopy(renderer, about, NULL, &about_Rect);
    SDL_RenderCopy(renderer, option, NULL, &option_rect);
}

//void createLevel(int level) {
//    threatObjects.clear(); // Xóa hết các đối tượng từ màn trước đó
//
//    // Tạo các threatObject cho màn chơi mới
//    int numThreatObjects = (level == 1) ? 4 : 7; // Số lượng threatObject sẽ tăng lên khi qua màn 1
//    for (int i = 0; i < numThreatObjects; ++i) {
//        int x = rand() % (1280 - 50);  // Tạo vị trí x ngẫu nhiên
//        int y = - rand() % 500;   // Tạo vị trí y ngẫu nhiên
//        int speed = 1;
//        char direction = (rand() % 2 == 0) ? 'L' : 'R'; // Chọn hướng di chuyển ngẫu nhiên
//        threatObjects.push_back(ThreatObject{ x, y, speed, direction });
//    }
//    
//}

void renderText(const std::string& text, int x, int y, int fontSize, SDL_Renderer* renderer) {
    
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return;
    }

    SDL_Rect textRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &textRect);

    // Clean up resources
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}
void gameover()
{
    string strscore = "Your score:"+ to_string(score);
    SDL_Surface* over = TTF_RenderText_Solid(font, strscore.c_str(), color);
    SDL_Texture* gover = SDL_CreateTextureFromSurface(renderer, over);
   
    int* x = new int(300);
    int* y = new int(300);
    SDL_QueryTexture(gover, NULL, NULL, x, y);
    SDL_Rect* vt = new SDL_Rect{  0,0, 600, 100 };
    SDL_RenderCopy(renderer, gover, NULL, vt);  
    SDL_FreeSurface(over);
    SDL_DestroyTexture(gover);
}

//void createLevel1() {
//    threatObjects.clear();
//    for (int i = 0; i < 4; ++i) {
//        int x = rand() % (1280 - 50);
//        int y = -rand() % 500;
//        int speed = 1;
//        char direction = (rand() % 2 == 0) ? 'L' : 'R';
//        threatObjects.push_back(ThreatObject{ x, y, speed, direction });
//    }
//}
//
//void createLevel2() {
//    threatObjects.clear();
//    for (int i = 0; i < 7; ++i) {
//        int x = rand() % (1280 - 50);
//        int y = -rand() % 500;
//        int speed = 1;
//        char direction = (rand() % 2 == 0) ? 'L' : 'R';
//        threatObjects.push_back(ThreatObject{ x, y, speed, direction });
//    }
//}

//void createLevel3() {
//    threatObjects.clear();
//    for (int i = 0; i < 7; ++i) {
//        int x = rand() % (1280 - 50);
//        int y = -rand() % 500;
//        int speed = 1;
//        char direction = (rand() % 2 == 0) ? 'L' : 'R';
//        threatObjects.push_back(ThreatObject{ x, y, speed, direction });
//    }
//    for (auto& obj : threatObjects) {
//        obj.timeBetweenShots = (rand() % 7 + 5);
//    }
//}

//void createLevel4() {
//    threatObjects.clear();
//    for (int i = 0; i < 10; ++i) {
//        int x = rand() % (1280 - 50);
//        int y = -rand() % 500;
//        int speed = 1;
//        char direction = (rand() % 2 == 0) ? 'L' : 'R';
//        threatObjects.push_back(ThreatObject{ x, y, speed, direction });
//    }
//    for (auto& obj : threatObjects) {
//        obj.timeBetweenShots = (rand() % 7 + 5);
//    }
//}
void createLevel(int level) {
    threatObjects.clear(); 

    
    switch (level) {
    case 1:
        for (int i = 0; i < 4; ++i) {
            int x = rand() % (1280 - 50); 
            int y = rand() % (100 - 50);   
            int speed = 0;
            char direction = (rand() % 2 == 0) ? 'L' : 'R'; 
            threatObjects.push_back(ThreatObject{ x, y, speed, direction });
        }
        break;
    case 2:
        for (int i = 0; i < 5; ++i) {
            int x = rand() % (1280 - 50);  
            int y =  (rand() % (100 - 50));   
            int speed = 0;
            char direction = (rand() % 2 == 0) ? 'L' : 'R'; 
            threatObjects.push_back(ThreatObject{ x, y, speed, direction });
        }
        break;
    case 3:
        for (int i = 0; i < 4; ++i) {
            int x = rand() % (1280 - 50);  
            int y = - (rand() % (200 - 50));   
            int speed = 1;
            char direction = (rand() % 2 == 0) ? 'L' : 'R'; 
            threatObjects.push_back(ThreatObject{ x, y, speed, direction });
        }
        break;
    case 4:
        for (int i = 0; i < 5; ++i) {
            int x = rand() % (1280 - 50);  
            int y = -(rand() % (200 - 50));   
            int speed = 1;
            char direction = (rand() % 2 == 0) ? 'L' : 'R'; 
            threatObjects.push_back(ThreatObject{ x, y, speed, direction });
        }
        break;
    case 5:
        for (int i = 0; i < 6; ++i) {
            int x = rand() % (1280 - 50);  
            int y = -(rand() % (300 - 50));   
            int speed = 1;
            char direction = (rand() % 2 == 0) ? 'L' : 'R'; 
            threatObjects.push_back(ThreatObject{ x, y, speed, direction });
        }
        break;
    case 6:
        for (int i = 0; i < 5; ++i) {
            int x = rand() % (1280 - 50);  
            int y = -(rand() % (300 - 50));  
            int speed = 1;
            char direction = (rand() % 2 == 0) ? 'L' : 'R'; 
            threatObjects.push_back(ThreatObject{ x, y, speed, direction });
        }
        for (int i = 0; i < 4; ++i) {
            int x = rand() % (1280 - 50);  
            int y = rand() % (100 - 50);  
            int speed = 0;
            char direction = (rand() % 2 == 0) ? 'L' : 'R'; 
            threatObjects.push_back(ThreatObject{ x, y, speed, direction });
        }
        
        break;
    
        
    default:
        
        break;
    }
}

void endinggame(SDL_Renderer* renderer)
{
    ending_rect.x = 0;
    ending_rect.y = 0;
    ending_rect.w = 1280;
    ending_rect.h = 680;
    SDL_RenderCopy(renderer, ending, NULL, &ending_rect);
}

void soundEffect()
{
    

    Mix_Chunk* bulletSound = Mix_LoadWAV("Tieng-bom-no-www_yeualo_com (mp3cut.net).mp3");
    if (bulletSound == NULL) {
        printf("Failed to load bullet sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }
    Mix_VolumeChunk(bulletSound, 40); 

    Mix_PlayChannel(-1, bulletSound, 0);
   

}
void gameoverover()
{
    
    SDL_Surface* over = TTF_RenderText_Solid(font, "GAME OVER", color);
    SDL_Texture* gover = SDL_CreateTextureFromSurface(renderer, over);

    int* x = new int(300);
    int* y = new int(300);
    SDL_QueryTexture(gover, NULL, NULL, x, y);
    SDL_Rect* vt = new SDL_Rect{ 350,300, 600, 100 };
    SDL_RenderCopy(renderer, gover, NULL, vt);
    SDL_FreeSurface(over);
    SDL_DestroyTexture(gover);
}

void gameabout1()
{

    SDL_Surface* over = TTF_RenderText_Solid(font, "Move the mouse and click to shoot bullets", color);
    SDL_Texture* gover = SDL_CreateTextureFromSurface(renderer, over);

    int* x = new int(300);
    int* y = new int(300);
    SDL_QueryTexture(gover, NULL, NULL, x, y);
    SDL_Rect* vt = new SDL_Rect{ 200,150, 700, 100 };
    SDL_RenderCopy(renderer, gover, NULL, vt);
    SDL_FreeSurface(over);
    SDL_DestroyTexture(gover);
}
void gameabout2()
{

    SDL_Surface* over = TTF_RenderText_Solid(font, "Survive and destroy as many enemies as possible", color);
    SDL_Texture* gover = SDL_CreateTextureFromSurface(renderer, over);

    int* x = new int(300);
    int* y = new int(300);
    SDL_QueryTexture(gover, NULL, NULL, x, y);
    SDL_Rect* vt = new SDL_Rect{ 200,250, 700, 100 };
    SDL_RenderCopy(renderer, gover, NULL, vt);
    SDL_FreeSurface(over);
    SDL_DestroyTexture(gover);
}
void gameabout3()
{

    SDL_Surface* over = TTF_RenderText_Solid(font, "Press SPACE to PAUSE/RESUME", color);
    SDL_Texture* gover = SDL_CreateTextureFromSurface(renderer, over);

    int* x = new int(300);
    int* y = new int(300);
    SDL_QueryTexture(gover, NULL, NULL, x, y);
    SDL_Rect* vt = new SDL_Rect{ 200,450, 700, 100 };
    SDL_RenderCopy(renderer, gover, NULL, vt);
    SDL_FreeSurface(over);
    SDL_DestroyTexture(gover);
}
void overEndingGame(SDL_Renderer* renderer)
{
    bkgrover_rect.x = 0;
    bkgrover_rect.y = 0;
    bkgrover_rect.w = 1280;
    bkgrover_rect.h = 680;
    SDL_RenderCopy(renderer, bkgrover, NULL, &bkgrover_rect);
}

void pressPauseGame(SDL_Renderer* renderer)
{
    pauseG_rect.x = 0;
    pauseG_rect.y = 0;
    pauseG_rect.w = 1280;
    pauseG_rect.h = 680;
    SDL_RenderCopy(renderer, pauseG, NULL, &pauseG_rect);
}

//void selectCharacterImage(int index) {
//    if (index >= 0 && index < characterTextures.size()) {
//        // Cập nhật chỉ số của hình ảnh được chọn
//        selectedCharacterIndex = index;
//        // Cập nhật hình ảnh cho nhân vật
//        characterTexture = characterTextures[index];
//    }
//}
void showCharacterSelectionMenu() {
    ship1_rect.x = 100;
    ship1_rect.y = 100;
    ship1_rect.w = 100;
    ship1_rect.h = 100;

    ship2_rect.x = 200;
    ship2_rect.y = 100;
    ship2_rect.w = 100;
    ship2_rect.h = 100;

    ship3_rect.x = 100;
    ship3_rect.y = 200;
    ship3_rect.w = 100;
    ship3_rect.h = 100;

    ship4_rect.x = 200;
    ship4_rect.y = 200;
    ship4_rect.w = 100;
    ship4_rect.h = 100;

    ship5_rect.x = 500;
    ship5_rect.y = 500;
    ship5_rect.w = 100;
    ship5_rect.h = 100;

    khungoption_rect.x = 100;
    khungoption_rect.y = 100;
    khungoption_rect.w = 800;
    khungoption_rect.h = 300;

    SDL_RenderCopy(renderer, khungoption, NULL, &khungoption_rect);
    SDL_RenderCopy(renderer, ship1, NULL, &ship1_rect);
    SDL_RenderCopy(renderer, ship2, NULL, &ship2_rect);
    SDL_RenderCopy(renderer, ship3, NULL, &ship3_rect);
    SDL_RenderCopy(renderer, ship4, NULL, &ship4_rect);
    SDL_RenderCopy(renderer, ship5, NULL, &ship5_rect);
}

void handleCharacterSelectionEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_1)
        {
            selectedCharacter == 1;
        }
        else if (e.key.keysym.sym == SDLK_2)
        {
            selectedCharacter == 2;
        }
        else if (e.key.keysym.sym == SDLK_3)
        {
            selectedCharacter == 3;
        }
        else if (e.key.keysym.sym == SDLK_4)
        {
            selectedCharacter == 4;
        }
        else if (e.key.keysym.sym == SDLK_5)
        {
            selectedCharacter == 5;
        }
        //// Xác định vị trí chuột
        //int mouseX = e.button.x;
        //int mouseY = e.button.y;

        //if (mouseX >= ship1_rect.x && mouseX < ship1_rect.x + ship1_rect.w &&
        //    mouseY >= ship1_rect.y && mouseY < ship1_rect.y + ship1_rect.h) {
        //    //selectCharacterImage(0); // Chọn hình ảnh đầu tiên
        //    selectedCharacter = 1;
        //}
        //else if (mouseX >= ship2_rect.x && mouseX < ship2_rect.x + ship2_rect.w &&
        //    mouseY >= ship2_rect.y && mouseY < ship2_rect.y + ship2_rect.h) {
        //    //selectCharacterImage(1); // Chọn hình ảnh đầu tiên
        //    selectedCharacter = 2;
        //}
        //else if (mouseX >= ship3_rect.x && mouseX < ship3_rect.x + ship3_rect.w &&
        //    mouseY >= ship3_rect.y && mouseY < ship3_rect.y + ship3_rect.h) {
        //    //selectCharacterImage(3); // Chọn hình ảnh đầu tiên
        //    selectedCharacter = 3;
        //}
        //else if (mouseX >= ship4_rect.x && mouseX < ship4_rect.x + ship4_rect.w &&
        //    mouseY >= ship4_rect.y && mouseY < ship4_rect.y + ship4_rect.h) {
        //    //selectCharacterImage(3); // Chọn hình ảnh đầu tiên
        //    selectedCharacter = 4;
        //}
        //else if (mouseX >= ship5_rect.x && mouseX < ship5_rect.x + ship5_rect.w &&
        //    mouseY >= ship5_rect.y && mouseY < ship5_rect.y + ship5_rect.h) {
        //    //selectCharacterImage(3); // Chọn hình ảnh đầu tiên
        //    selectedCharacter = 5;
        //}
    }
}

