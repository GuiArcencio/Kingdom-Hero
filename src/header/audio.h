#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

typedef struct AudioHandler {
    ALLEGRO_SAMPLE* somEspada;
    ALLEGRO_AUDIO_STREAM* musica;
    ALLEGRO_SAMPLE_ID* idEspada;
} AudioHandler;

AudioHandler* audio_load(); // Inicializar audio
void audio_espada(AudioHandler* a); // Tocar o som da espada

void audio_musica(AudioHandler* a, bool tocar); // Parar ou recomeçar a música

void destroy_audio(AudioHandler* a); // Destruir o audio