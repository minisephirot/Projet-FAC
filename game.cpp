#include <math.h>
#include <SDL/SDL_mixer.h>
#include "game.h"
#include "lib_fst.h"
#include "sdlglutils.h"
#include "accueil.h"
#include "ennemis.h"




int gameStart(){

/*  *****************
    * Les Variables *
    *****************  */

    // variable annoncant la fin de jeu
    int exit, choix;
    int i;
    int Lasttime = 0, Time = 0, Timer = 10;
    int scorejoueur = 0, cd = 100;
    int centaine = 0 ;

    //Position de la camera
    double x, y, z, h;
    double dx, dy;
    //direction
    double direc;
    bool monter = false;

    //Touche directionnelle
    bool w=false;
    bool spc=false;
    bool s=false;
    bool a=false;
    bool d=false;
    bool azerty = false;
    bool F3 = false;
    bool F4 = false;
    bool player = false;
    bool esc=false;
    bool fgauche=false;
    bool fdroite=false;
    bool fhaut=false;
    bool fbas=false;

/*  *****************
    *     Debut     *
    *****************  */


    //---------Initialisation des variables---------
     exit=1;
     choix = 1;
     x = TAILLE_CUBES*2;
     y = TAILLE_CUBES*2;
     z = 20;
     h = 0;
     direc = 0;

    //---------Génération des Ennemis et du bonus---------
    //****************************************

	const int ncubes = 3;
	const int nbonus = 1;
        Ennemis cubes[ncubes];
        Bonus scoring[nbonus];

        //---------Enemis 1---------
          cubes[0].x = TAILLE_PLATEAU*(TAILLE_CUBES)-(4*TAILLE_CUBES)+40;
          cubes[0].y = TAILLE_PLATEAU*(TAILLE_CUBES)-(5*TAILLE_CUBES);
          cubes[0].direc = 65;

        //---------Enemis 2---------
          cubes[1].x = (TAILLE_PLATEAU*(TAILLE_CUBES))/2;
          cubes[1].y = (TAILLE_PLATEAU*(TAILLE_CUBES))/2;
          cubes[1].direc = 37;
        //---------Enemis 3---------
          cubes[2].x = TAILLE_PLATEAU*(TAILLE_CUBES)-(4*TAILLE_CUBES);
          cubes[2].y = 5*(TAILLE_CUBES);
          cubes[2].direc = -45;
        //---------Bonus-----------
          scoring[0].x = ((TAILLE_CUBES*TAILLE_PLATEAU)-TAILLE_CUBES)/2;
          scoring[0].y = ((TAILLE_CUBES*TAILLE_PLATEAU)-TAILLE_CUBES)/2;
          scoring[0].z = 9;

    //---------Fin de la génération---------
    //**************************************


    //---------initialisation de la fenetre---------
    sdl3d(800,600, 100);
    SDL_WM_SetCaption("Arcade : Cube", NULL);
    SDL_EnableKeyRepeat(10, 10); //Permet la répétition des entrées de clavier toute les 10ms
    //Init audio
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
    Mix_AllocateChannels(10);
    //---------initialisation des textures & sons---------
    glEnable(GL_TEXTURE_2D);
    GLuint texture1 = loadTexture("texture/ciel.jpg",false); //pour les false, voir sdlglutils.cpp ligne 54
    GLuint texture2 = loadTexture("texture/mur.jpg",false);
    GLuint texture3 = loadTexture("texture/sol2.jpg",false);
    GLuint texture4 = loadTexture("texture/cieluni.jpg",false);
    GLuint texture5 = loadTexture("texture/piece.jpg",false);
    GLuint texture6 = loadTexture("texture/thwomp.jpg",false);
    GLuint texture7 = loadTexture("texture/hud.png",false);
    GLuint texture8 = loadTexture("texture/cryo.png",false);
    GLuint texture9 = loadTexture("texture/sol.jpg",false);
    GLuint texturen0 = loadTexture("texture/0.png",false);
    GLuint texturen1 = loadTexture("texture/1.png",false);
    GLuint texturen2 = loadTexture("texture/2.png",false);
    GLuint texturen3 = loadTexture("texture/3.png",false);
    GLuint texturen4 = loadTexture("texture/4.png",false);
    GLuint texturen5 = loadTexture("texture/5.png",false);
    GLuint texturen6 = loadTexture("texture/6.png",false);
    GLuint texturen7 = loadTexture("texture/7.png",false);
    GLuint texturen8 = loadTexture("texture/8.png",false);
    GLuint texturen9 = loadTexture("texture/9.png",false);
    Mix_Music *musicbg = Mix_LoadMUS("texture/bomb.mp3");
    Mix_Chunk *walk = Mix_LoadWAV("texture/grass.wav");
    Mix_Chunk *ding = Mix_LoadWAV("texture/ding.wav");
    Mix_Chunk *thwomp = Mix_LoadWAV("texture/thwomp.wav");
    Mix_FadeInMusic(musicbg, -1,3000);
    Mix_VolumeMusic(6);
    Mix_VolumeChunk(walk,10);
    Mix_VolumeChunk(thwomp,4);
    Mix_VolumeChunk(ding,10);

    //---------Fichier sauvegarde---------
    FILE* fichier = NULL;
    int scoretab[6]={0};


    /************************
     *     Debut du jeu     *
     ************************/

    //Parametre de direction des cubes énnemis
    for (i=0; i<ncubes; i++) {
      cubes[i].dx = cos(cubes[i].direc*M_PI/180)*VITESSE_DEPLACEMENT;
      cubes[i].dy = sin(cubes[i].direc*M_PI/180)*VITESSE_DEPLACEMENT;
    }

    while(exit)
    {

    //-------Actualisation tout les  10ms---
      Time = SDL_GetTicks();
      if (Time - Lasttime > Timer) {

        Lasttime = Time;
        //---------Début Des Events---------
          SDL_PumpEvents();
          dx = cos(direc*M_PI/180)*VITESSE_DEPLACEMENT;
          dy = sin(direc*M_PI/180)*VITESSE_DEPLACEMENT;
          Uint8 *keystates = SDL_GetKeyState(NULL);


          if(!azerty){
            w = keystates[SDLK_w];
            s = keystates[SDLK_s];
            a = keystates[SDLK_a];
            d = keystates[SDLK_d];
          }
          else
          {
            w = keystates[SDLK_z];
            s = keystates[SDLK_s];
            a = keystates[SDLK_q];
            d = keystates[SDLK_d];
          }
          esc = keystates[SDLK_ESCAPE];
          fgauche = keystates[SDLK_LEFT];
          fdroite = keystates[SDLK_RIGHT];
          fhaut = keystates[SDLK_UP];
          fbas = keystates[SDLK_DOWN];
          spc = keystates[SDLK_SPACE];
          F3 = keystates[SDLK_F3];
          F4 = keystates[SDLK_F4];

          // Fin du jeu : echap ou fermé
           SDL_Event event;
           SDL_PollEvent(&event);
           if ((esc) || (event.type == SDL_QUIT)){
             exit=0;
             choix = 1;
           }

           //choix clavier/debugage
           if (event.key.keysym.sym == SDLK_F1)
           {
             if (azerty == true)
               azerty = false;
           }
           if (event.key.keysym.sym == SDLK_F2)
           {
             if (azerty == false)
               azerty = true;
           }
           if (F3){
            F4 = false;
            z = 400;
            player = true;
           }
           if (F4){
            F3 = false;
            z = 20;
            player = false;
           }
        //---------Fin Des Events---------

        //Déplcement de la caméra sur l'axe x et y
        if (w){
          x += dx;
          y += dy;
          if (Mix_Playing(1) == 0) { Mix_PlayChannel(1, walk, 0); }
        }
        if (s){
          x -= dx;
          y -= dy;
          if (Mix_Playing(1) == 0) { Mix_PlayChannel(1, walk, 0); }
        }
        if (a){
          x -= dy;
          y += dx;
          if (Mix_Playing(1) == 0) { Mix_PlayChannel(1, walk, 0); }
        }
        if (d){
          x += dy;
          y -= dx;
          if (Mix_Playing(1) == 0) { Mix_PlayChannel(1, walk, 0); }
        }
        if (fgauche){
          direc=direc+VITESSE_ORIENTATION;
        }
        if (fdroite){
          direc=direc-VITESSE_ORIENTATION;
        }
        if (fhaut){
         if (h < 5) {
          h=h+0.15;
          }
        }
        if (fbas){
         if (h > -5) {
          h=h-0.15;
          }
        }
        if (spc && cd > 0){
          Timer=20;
          cd -= 1;
        }
        else {
          Timer = 10;
          if(spc == false && cd < 100)
          {
           cd += 1;
          }
        }


        //---------Gestion des collisions---------
        if (x <= ((TAILLE_CUBES/2)+2)){
          x = x + TAILLE_CUBES/7;
        }
        if (x >= (((TAILLE_CUBES*TAILLE_PLATEAU)-TAILLE_CUBES/2)-2)){
          x = x - TAILLE_CUBES/7;
        }
        if (y >= (((TAILLE_CUBES*TAILLE_PLATEAU)-TAILLE_CUBES/2)-2)){
          y = y - TAILLE_CUBES/7;
        }
        if (y <= ((TAILLE_CUBES/2)+2)){
          y = y + TAILLE_CUBES/7;
        }

        //---------Gestion des Collisions aux Ennemis---------
        for (i=0; i<ncubes; i++){
          if (x >= (((cubes[i].x)-TAILLE_CUBES/2)-7) &&
            x <= (((cubes[i].x)+TAILLE_CUBES/2)+7) &&
            y >= (((cubes[i].y)-TAILLE_CUBES/2)-7) &&
            y <= (((cubes[i].y)+TAILLE_CUBES/2)+7))
            {
                Mix_FadeOutMusic(2000);
                exit=0;
                choix= gameover();
            }
        }
        for (int i=0; i<=nbonus-1; i++)
        {
            if (scoring[i].z > 19)
            {
                monter = false;
            }
            if (scoring[i].z < 3)
            {
                monter = true;
            }
            if (monter == true)
            {
                scoring[i].z = scoring[i].z + 0.4;
            }
            if (monter == false)
            {
                scoring[i].z = scoring[i].z - 0.4;
            }
            if (x >= (((scoring[i].x)-25/2)-7) &&
            x <= (((scoring[i].x)+25/2)+7) &&
            y >= (((scoring[i].y)-25)-7) &&
            y <= (((scoring[i].y)+25)+7))
            {
                if (Mix_Playing(3) == 0) { Mix_PlayChannel(3, ding, 0); }
                scorejoueur = (scorejoueur+10);
                scoring[i].x= rand() % ((TAILLE_CUBES*TAILLE_PLATEAU)-80) + (TAILLE_PLATEAU+6);
                scoring[i].y= rand() % ((TAILLE_CUBES*TAILLE_PLATEAU)-80) + (TAILLE_PLATEAU+6);
            }
        }
        //---------Fin de la gestion des collisions---------


        // La variable b n'a pas besoin d'etre plus grand que 360
        direc = direction(direc);

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        camera(x,y,z,x+dx,y+dy,20+h); //explication en annexe

        if (deplcementEnnemis(cubes, ncubes, scorejoueur+100,texture6) == 1 ) {
            if (Mix_Playing(2) == 0) { Mix_PlayChannel(2, thwomp, 0); }
        }
        generationbonus(scoring, nbonus, texture5);

        if (player) {
            glBindTexture(GL_TEXTURE_2D,texture9);
            cube_position(11,x,y,10,0,0,0);
        }

        //---------Debut Du Plateau & HUD---------


          //ciel en fond
          glBindTexture(GL_TEXTURE_2D, texture1);
          cube_position(TAILLE_PLATEAU*TAILLE_CUBES/2,TAILLE_PLATEAU*TAILLE_CUBES/2,TAILLE_PLATEAU*TAILLE_CUBES/2, (TAILLE_PLATEAU*TAILLE_CUBES-TAILLE_CUBES)/2,0,0,0);
          //sol en fond
          glBindTexture(GL_TEXTURE_2D, texture3);
          plat_pos(TAILLE_PLATEAU*TAILLE_CUBES/2,TAILLE_PLATEAU*TAILLE_CUBES/2,TAILLE_PLATEAU*TAILLE_CUBES/2, (TAILLE_PLATEAU*TAILLE_CUBES-TAILLE_CUBES)/2+1,0,0,0);
          //plafond en fond
          glBindTexture(GL_TEXTURE_2D, texture4);
          plaf_pos(TAILLE_PLATEAU*TAILLE_CUBES/2,TAILLE_PLATEAU*TAILLE_CUBES/2,TAILLE_PLATEAU*TAILLE_CUBES/2, (TAILLE_PLATEAU*TAILLE_CUBES-TAILLE_CUBES)+(TAILLE_PLATEAU*TAILLE_CUBES/2),0,0,0);

          int i=0;
          while(i<=TAILLE_PLATEAU){
            glBindTexture(GL_TEXTURE_2D, texture2);
            cube_position(TAILLE_CUBES/2,TAILLE_PLATEAU*(TAILLE_CUBES),i*(TAILLE_CUBES),0,0,0,0);
            cube_position(TAILLE_CUBES/2,i*(TAILLE_CUBES),TAILLE_PLATEAU*(TAILLE_CUBES),0,0,0,0);
            cube_position(TAILLE_CUBES/2,i*(TAILLE_CUBES),0,0,0,0,0);
            cube_position(TAILLE_CUBES/2,0,i*(TAILLE_CUBES),0,0,0,0);
            cube_position(TAILLE_CUBES/2,TAILLE_PLATEAU*(TAILLE_CUBES),i*(TAILLE_CUBES),TAILLE_CUBES,0,0,0);
            cube_position(TAILLE_CUBES/2,i*(TAILLE_CUBES),TAILLE_PLATEAU*(TAILLE_CUBES),TAILLE_CUBES,0,0,0);
            cube_position(TAILLE_CUBES/2,i*(TAILLE_CUBES),0,TAILLE_CUBES,0,0,0);
            cube_position(TAILLE_CUBES/2,0,i*(TAILLE_CUBES),TAILLE_CUBES,0,0,0);
            i++;
          }
          //HUD
          if (spc && cd > 0) {
            glBindTexture(GL_TEXTURE_2D,texture8);
            interface();
          }
          //Affichage HUD des dizaines et centaines

          //dizaines
          int dizaines = choixscore(scorejoueur,&centaine) ;
          if (dizaines == 0) {
            glBindTexture(GL_TEXTURE_2D,texturen0) ;
            interface10();
          }
          if (dizaines == 1) {
            glBindTexture(GL_TEXTURE_2D,texturen1) ;
            interface10();
          }
          if (dizaines == 2) {
            glBindTexture(GL_TEXTURE_2D,texturen2) ;
            interface10();
          }
          if (dizaines == 3) {
            glBindTexture(GL_TEXTURE_2D,texturen3) ;
            interface10();
          }
          if (dizaines == 4) {
            glBindTexture(GL_TEXTURE_2D,texturen4) ;
            interface10();
          }
          if (dizaines == 5) {
            glBindTexture(GL_TEXTURE_2D,texturen5) ;
            interface10();
          }
          if (dizaines == 6) {
            glBindTexture(GL_TEXTURE_2D,texturen6) ;
            interface10();
          }
          if (dizaines == 7) {
            glBindTexture(GL_TEXTURE_2D,texturen7) ;
            interface10();
          }
          if (dizaines == 8) {
            glBindTexture(GL_TEXTURE_2D,texturen8) ;
            interface10();
          }
          if (dizaines == 9) {
            glBindTexture(GL_TEXTURE_2D,texturen9) ;
            interface10();
          }
          //fin des dizaines
          //centaines
          if (centaine == 0) {
            glBindTexture(GL_TEXTURE_2D,texturen0) ;
            interface100();
          }
          if (centaine == 1) {
            glBindTexture(GL_TEXTURE_2D,texturen1) ;
            interface100();
          }
          if (centaine == 2) {
            glBindTexture(GL_TEXTURE_2D,texturen2) ;
            interface100();
          }
          if (centaine == 3) {
            glBindTexture(GL_TEXTURE_2D,texturen3) ;
            interface100();
          }
          if (centaine == 4) {
            glBindTexture(GL_TEXTURE_2D,texturen4) ;
            interface100();
          }
          if (centaine == 5) {
            glBindTexture(GL_TEXTURE_2D,texturen5) ;
            interface100();
          }
          if (centaine == 6) {
            glBindTexture(GL_TEXTURE_2D,texturen6) ;
            interface100();
          }
          if (centaine == 7) {
            glBindTexture(GL_TEXTURE_2D,texturen7) ;
            interface100();
          }
          if (centaine == 8) {
            glBindTexture(GL_TEXTURE_2D,texturen8) ;
            interface100();
          }
          if (centaine == 9) {
            glBindTexture(GL_TEXTURE_2D,texturen9) ;
            interface100();
          }
          //fin des centaines


          glBindTexture(GL_TEXTURE_2D, texturen0 );
          interface0();

          glBindTexture(GL_TEXTURE_2D,texture7);
          interface();

        //---------Fin Du Plateau---------

        glFlush();
        SDL_GL_SwapBuffers();

      }//--Attente de 30ms
    }//--Fin de boucle

    /************************
    *      Fin du jeu      *
    ************************/
  Mix_FreeChunk(walk);
  Mix_FreeChunk(thwomp);
  Mix_FreeChunk(ding);
  Mix_FreeMusic(musicbg);
  Mix_CloseAudio();
  //---------Debut de sauvgarde---------
  fichier = fopen("score.txt","r");
  if (fichier != NULL){
    fscanf(fichier,"%d\n%d\n%d\n%d\n%d", &scoretab[0], &scoretab[1],&scoretab[2],&scoretab[3],&scoretab[4]);
    fclose(fichier);
  }
  scoretab[5]=scorejoueur;
  tri(6,scoretab);
  fichier = fopen("score.txt","w+");
  fprintf(fichier, "%d\n%d\n%d\n%d\n%d\n%d", scoretab[0], scoretab[1],scoretab[2],scoretab[3],scoretab[4],scoretab[5]);
  fclose(fichier);
  //---------fin de sauvgarde---------


  return choix;

/****************
 *     Fin      *
 ****************/
}






