#include "display.h"

static Uint8	*g_audio_pos;
static Uint8	*g_audio_init;
static Uint32	g_audio_curr;
static Uint32	g_audio_len;

void	music_callback(__attribute__((unused)) void *data,
		       Uint8 *music, int length)
{
  if (g_audio_len <= 0)
    return ;
  if (g_audio_curr <= 0)
    {
      g_audio_curr = g_audio_len;
      g_audio_pos = g_audio_init;
    }
  length = (length > (int)g_audio_curr) ? (int)g_audio_curr : length;
  SDL_memcpy(music, g_audio_pos, length);
  SDL_MixAudio(music, g_audio_pos, length, SDL_MIX_MAXVOLUME);
  g_audio_pos += length;
  g_audio_curr -= length;
}

int	launch_music(t_display *d)
{
  if (!SDL_LoadWAV("./assets/audio/music.wav",
		   &d->wav_spec, &d->wavbuff, &d->wavlen))
    return (-1);
  d->wav_spec.callback = music_callback;
  d->wav_spec.userdata = NULL;
  g_audio_init = d->wavbuff;
  g_audio_pos = d->wavbuff;
  g_audio_len = d->wavlen;
  g_audio_curr = d->wavlen;
  if (SDL_OpenAudio(&d->wav_spec, NULL) < 0)
    return (-1);
  SDL_PauseAudio(0);
  d->music_on = 1;
  return (0);
}
