//
// Created by screemer on 2019-03-02.
//

#include "gui_btn_guide.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../gui/gui.h"
#include "../lang.h"
#include "../engine/scanner.h"

using namespace std;

//*******************************
// GuiBtnGuide::render
//*******************************
void GuiBtnGuide::render() {
    shared_ptr<Gui> gui(Gui::getInstance());
    gui->renderBackground();

    gui->renderTextBar();
    int offset = gui->renderLogo(true);
    gui->renderTextLine("-=" + _("Button Guide") + "=-", 0, offset, POS_CENTER);
    gui->renderTextLine(_("DPAD - Same as classic menu"), 1, offset, POS_CENTER);
    gui->renderTextLine("|@X| / |@O|   " + _("Select or cancel highlighted option"), 2, offset, POS_CENTER);
    gui->renderTextLine("|@S|   " + _("Run using RetroBoot(if installed)"), 3, offset, POS_CENTER);
    gui->renderTextLine("|@R1| / |@L1|   " + _("Quick scroll to next letter"), 4, offset, POS_CENTER);
    gui->renderTextLine("|@Select|   " + _("Games filter"), 5, offset, POS_CENTER);
    gui->renderTextLine("|@L2| + |@Select|   " + _("RetroBoot Systems"), 6, offset, POS_CENTER);

    gui->renderTextLine("-=" + _("In Game") + "=-", 8, offset, POS_CENTER);
    gui->renderTextLine("|@Select| + |@T|   " + _("Emulator config MENU"), 9, offset, POS_CENTER);
    gui->renderTextLine("RESET   " + _("Quit emulation - back to AutoBleem"), 10, offset, POS_CENTER);

    gui->renderTextLine("|@R2| + |@L2|  " + _("IN BOOT MENU TO POWER OFF THE CONSOLE (SAFE POWER OFF !!!)"), 12, offset,
                        POS_CENTER);


    gui->renderStatus("|@O| " + _("Go back") + "|");
    SDL_RenderPresent(renderer);
}

//*******************************
// GuiBtnGuide::loop
//*******************************
void GuiBtnGuide::loop() {
    shared_ptr<Gui> gui(Gui::getInstance());
    bool menuVisible = true;
    while (menuVisible) {
        gui->watchJoystickPort();
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.scancode == SDL_SCANCODE_SLEEP) {
                    gui->drawText(_("POWERING OFF... PLEASE WAIT"));
                    Util::powerOff();

                }
            }
            // this is for pc Only
            if (e.type == SDL_QUIT) {
                menuVisible = false;
            }
            switch (e.type) {
                case SDL_JOYBUTTONUP:


                    if (e.jbutton.button == gui->_cb(PCS_BTN_CIRCLE, &e)) {
                        Mix_PlayChannel(-1, gui->cancel, 0);
                        menuVisible = false;

                    };


            }

        }
    }
}
