#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include <string.h>

//fontion affiche gagnant et joue musique

void winner(char *nom){
  MLV_init_audio();
  MLV_Music* music=MLV_load_music("assets/winner.mp3");
  int width=800, height=800;
  int width_text, height_text;
  char text[30]="Gagnant ";
  strcat(text, nom);
  MLV_get_size_of_text(text, &width_text, &height_text);
  int positionX=0.35*width, positionY=0.5*height;
  MLV_play_music(music, 2.0, -1);
  MLV_draw_adapted_text_box(positionX,positionY, text, 10,MLV_COLOR_RED,MLV_COLOR_GREEN,MLV_COLOR_BLUE,MLV_TEXT_CENTER);
  MLV_actualise_window();
  MLV_wait_seconds(30);
  MLV_stop_music();
  MLV_free_music(music);
  MLV_free_audio();
}

//fonction bruit de carte qui se pose

void son_pose(){
  MLV_Sound* sound;
  sound = MLV_load_sound("assets/posecartes.mp3");
  MLV_play_sound(sound, 1.0);
  MLV_stop_all_sounds();
  MLV_free_sound(sound);
  MLV_free_audio();
}

//fonction bruit de mélange de cartes

void son_mel(){
  MLV_Sound* sound;
  sound = MLV_load_sound("assets/dist.mp3");
  MLV_play_sound(sound, 1.0);
  MLV_stop_all_sounds();
  MLV_free_sound(sound);
  MLV_free_audio();
}

int main(){
  MLV_create_window("text", "text", 800, 800);
  winner("J1");
  son_pose();
  son_mel();
  return 0;
}
