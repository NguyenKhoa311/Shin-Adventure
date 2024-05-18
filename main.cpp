#include "Game.h"
#include "Menu.h"

int main(int argc, char *argv[]) {
    Game::Init();
    SDL_Renderer* m_renderer = Game::GetRenderer();
    Menu* GameMenu;
    GameMenu = new Menu();
    GameMenu->SetUp(m_renderer);

    Home:
    int i = GameMenu->ShowMenu(m_renderer);

    if (i == 1) {
        //exit
        goto End;
    }
    else if (i == 2) {
        //game instruction
        BaseObject baseObject;
        baseObject.LoadImg("image/Instruction.png", m_renderer);
        while (true) {
            SDL_Event m_event;
            baseObject.Render(m_renderer,0,0);
            SDL_RenderPresent(m_renderer);
            while (SDL_PollEvent(&m_event)) {
                switch(m_event.type) {
                    case SDL_QUIT:
                        exit(0);
                    case SDL_KEYDOWN:
                        switch(m_event.key.keysym.sym) {
                            case SDLK_ESCAPE: break;
                            case SDLK_SPACE:
                                baseObject.Free();
                                goto Home;
                        }
                }
            }
        }
    }
    else
    {
        //play game
        Replay:
            Game* game = new Game();
            game->RunGameLoop();

            if(Game::quit)
            {
                delete game;
                goto End;
            }

            SDL_SetRenderDrawColor(m_renderer, 0,0,0,0);
            int option = GameMenu->endMenu(m_renderer);
            delete game;

            if (option == 0) {
                    GameMenu->FreeEndMenu();
                    goto Replay;
            }
            else if (option == 2) {
                SDL_RenderClear(m_renderer);
                GameMenu->FreeEndMenu();
                goto Home;
            }
            else
            {
                game->FreeObject();
            }
    }

    End:
    delete GameMenu;
    Game::Quit();
    return 0;
}

// Comment test

