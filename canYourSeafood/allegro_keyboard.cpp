void key_board(ALLEGRO_EVENT event , bool *redraw, char *name){
    if (event.type == ALLEGRO_EVENT_KEY_DOWN){
        *redraw = true;
        if(strlen(name)<10){
            if(event.keyboard.keycode<=36 && event.keyboard.keycode>=1){
                al_play_sample(sound1, 2.5, 0, 1.0, ALLEGRO_PLAYMODE_ONCE,0); /// 打字音效撥放

                char ch[2]={};
                if(event.keyboard.keycode<=26)
                    ch[0]='A'+event.keyboard.keycode-1; /// A ~ Z 
                else
                    ch[0]='0'+event.keyboard.keycode-27; /// 0 ~ 9
                strcat(name,ch);
            }
        }
        if(event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE){
            if(strlen(name)>0)
                name[strlen(name)-1]='\0';
        }
    }
}

/**
去年 C 的垃圾寫法
交給紅葉大師優化 ~~~

redraw : if name change -> redraw = true
name : 
	
	if ( name.length() < 10 (max length = 10) ) {
		if (key = A ~ Z | 0 ~ 9 ){
			play SE (sound effect);
			name = {name, key};
		}
	}
	if (key = Backspace (刪除) ) & (name != "")
		name.pop_back;
		

ALLEGRO_KEY_A  ~  ALLEGRO_KEY_Z  =  1 ~ 26
ALLEGRO_KEY_0  ~  ALLEGRO_KEY_9  =  27 ~ 36
ALLEGRO_KEY_BACKSPACE = 63


**/