#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

typedef struct AudioHandler {
    ALLEGRO_SAMPLE* somEspada;
    ALLEGRO_AUDIO_STREAM* musica;
    ALLEGRO_SAMPLE_ID* idEspada;
} AudioHandler;

AudioHandler* audio_load();
void audio_espada(AudioHandler* a);

void audio_musica(AudioHandler* a, bool tocar);

void destroy_audio(AudioHandler* a);