//
// Created by miste on 3/8/2026.
//

#ifndef LAVENDERENGINE_AUDIOENGINE_H
#define LAVENDERENGINE_AUDIOENGINE_H
#include "miniaudio.h"
#include <string>

namespace lavender::audio {
    class AudioEngine{
    public:
        static bool init();
        static void playSound(const std::string& filePath);
        // TODO: add other audio calls like looping, sound track etc
        // TODO: add multiprocessing to play multiple sounds at once
        static void shutdown();

    private:
        static ma_engine engine;
        static bool initialized;

    };
}


#endif //LAVENDERENGINE_AUDIOENGINE_H