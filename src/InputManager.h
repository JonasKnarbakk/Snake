/*
 * @file: InputManager.h
 * @version: 2.0.3 <12.03.2015>
 * @author: Tomas Sandnes <santom@nith.no> - 2009 & 2015
 * @author: Kjetil Raaen <raakje@nith.no> - 2011
 * @author: Stig M. Halvorsen <halsti@nith.no> - 2013
 *
 * @description: A singleton State Snapshot input manager
 *				 using SDL2 for interactive input.
 *				 This is platform independent!
 */

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <memory>
#include <SDL.h>

class InputManager {
  public:
    /* Standard Meyer's singleton instance call to access the object */
    static InputManager &Instance() {
        static InputManager iM;
        return iM;
    }

    /* Updates the key states */
    void Update();

    /* Whether the user has closed the window (X-ed out the window) */
    inline bool hasExit() const {
        return m_exit;
    };

    // Inline keyboard functions.
    bool KeyDown(int keyIndex) const {
        return (CurKeyDown(keyIndex)) && (!OldKeyDown(keyIndex));
    }
    bool KeyStillDown(int keyIndex) const {
        return (CurKeyDown(keyIndex)) && (OldKeyDown(keyIndex));
    }
    bool KeyUp(int keyIndex) const {
        return (!CurKeyDown(keyIndex)) && (OldKeyDown(keyIndex));
    }
    bool KeyStillUp(int keyIndex) const {
        return (!CurKeyDown(keyIndex)) && (!OldKeyDown(keyIndex));
    }

    // Inline mouse functions.
    bool MouseDown(int button) {
        return (CurMouseDown(button)) && (!OldMouseDown(button));
    }
    bool MouseStillDown(int button) {
        return (CurMouseDown(button)) && (OldMouseDown(button));
    }
    bool MouseUp(int button) {
        return (!CurMouseDown(button)) && (OldMouseDown(button));
    }
    bool MouseStillUp(int button) {
        return (!CurMouseDown(button)) && (!OldMouseDown(button));
    }

  protected:
    // Helper functions to make things easier.
    bool CurKeyDown(const int &keyIndex) const {
        return (m_keys[keyIndex] != 0);
    }
    bool OldKeyDown(const int &keyIndex) const {
        return (m_oldKeys.get()[keyIndex] != 0);
    }
    bool CurMouseDown(const int &button) const {
        return (m_mouseButtons & SDL_BUTTON(button)) != 0;
    }
    bool OldMouseDown(const int &button) const {
        return (m_oldMouseButtons & SDL_BUTTON(button)) != 0;
    }

    const Uint8 *m_keys;              // A pointer to SDL's internal key state array. (Memory handled by SDL.)
    std::unique_ptr<Uint8> m_oldKeys; // Our own copy of last update's array. NB! Memory handled dynamically by us!
    int m_keyCount; // Number of keys in the arrays above, for this application. (Can vary depending on setup/hardware.)

    int m_mouseX;            // Mouse pos x.
    int m_mouseY;            // Mouse pos y.
    Uint8 m_mouseButtons;    // Mouse buttons clicked
    Uint8 m_oldMouseButtons; // Mouse buttons clicked last update
    bool m_exit;             // If the user has closed the window or not (X)
  private:
    InputManager();                                // Hidden constructor
    InputManager(const InputManager &);            // Hidden copy constructor
    InputManager &operator=(const InputManager &); // Hidden assign operator
};

#endif