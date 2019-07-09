#include "header/audio.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdlib.h>

AudioHandler* audio_load() {
    AudioHandler* handler = (AudioHandler*) malloc(sizeof(AudioHandler));
    if (handler == NULL) exit(1);
    al_reserve_samples(5);


    handler->musica = al_load_audio_stream("./sound/musica.ogg", 4, 1024);
    handler->somEspada = al_load_sample("./sound/swoosh.wav");
    handler->idEspada = NULL;
    al_attach_audio_stream_to_mixer(handler->musica, al_get_default_mixer());
    al_set_audio_stream_playmode(handler->musica, ALLEGRO_PLAYMODE_LOOP);

    return handler;
}

void audio_espada(AudioHandler* a) {
    // Se um som de espada anterior foi tocado, cancele-o antes de tocar o próximo
    if (a->idEspada != NULL)
        al_stop_sample(a->idEspada);
    al_play_sample(a->somEspada, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, a->idEspada);
}

void destroy_audio(AudioHandler* a) {
    al_destroy_sample(a->somEspada);
    al_destroy_audio_stream(a->musica);
    free(a);
}

void audio_musica(AudioHandler* a, bool tocar) {
    // Se a música começar a tocar novamente, reinicie ela
    if (tocar) al_rewind_audio_stream(a->musica);
    al_set_audio_stream_playing(a->musica, tocar);
}