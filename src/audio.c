#include "header/audio.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdlib.h>

AudioHandler* audio_load() {
    AudioHandler* handler = (AudioHandler*) malloc(sizeof(AudioHandler));
    if (handler == NULL) exit(1);
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(5);

    handler->musica = NULL;
    handler->somEspada = al_load_sample("./sound/swoosh.wav");
    handler->idEspada = NULL;

    return handler;
}

void audio_espada(AudioHandler* a) {
    if (a->idEspada != NULL)
        al_stop_sample(a->idEspada);
    al_play_sample(a->somEspada, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, a->idEspada);
}

void destroy_audio(AudioHandler* a) {
    al_destroy_sample(a->somEspada);
    free(a);
}