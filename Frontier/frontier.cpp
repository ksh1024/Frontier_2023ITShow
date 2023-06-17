//중앙 배치 setPosition(player_pos.x +이미지가로 / 2 + 75 - 이미지가로, player_pos.y + 이미지세로 / 2 - (이미지세로 - 75));
//75는 뭐지..............???

//TODO
//대사 메모장에서 불러오기로 변경?
//선택지
//맵 
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <ctime>
#include <SFML/Audio.hpp>
#include <iostream>
#include <String> //대사
#include <string> //cout

#define _CRT_SECURE_NO_WARNINGS

using namespace std;
using namespace sf;

struct Textures {
    Texture title_bg;
    Texture home_bg;

    Texture start_btn_def;
    Texture quit_btn_def;
    Texture start_btn_sel;
    Texture quit_btn_sel;

    Texture main_ch_front_x;
    Texture main_ch_right_x;
    Texture main_ch_left_x;
    Texture main_ch_back_x;

    Texture main_ch_front_o;
    Texture main_ch_right_o;
    Texture main_ch_left_o;
    Texture main_ch_back_o;

    Texture main_ch_w_f_x_1;
    Texture main_ch_w_f_x_2;
    Texture main_ch_w_f_x_3;
    Texture main_ch_w_f_x_4;

    Texture main_ch_w_b_x_1;
    Texture main_ch_w_b_x_2;


    Texture main_ch_w_l_x_1;
    Texture main_ch_w_l_x_2;
    Texture main_ch_w_l_x_3;
    Texture main_ch_w_l_x_4;

    Texture main_ch_w_r_x_1;
    Texture main_ch_w_r_x_2;
    Texture main_ch_w_r_x_3;
    Texture main_ch_w_r_x_4;


    Texture pet_f;
    Texture pet_b;
    Texture pet_l;
    Texture pet_r;

    //아이템 후광있는 이미지
    Texture item_frism;
    Texture item_piston;
    Texture item_speaker;
    Texture item_belt;
    Texture item_bolt;
    Texture item_bridge;
    Texture item_line;
    Texture item_stick;
    Texture item_wiyer;
    Texture item_zender;

    Texture halo;
    //아이템 후광 없는 이미지
    Texture item_frism_show;
    Texture item_piston_show;
    Texture item_speaker_show;
    Texture item_belt_show;
    Texture item_bolt_show;
    Texture item_bridge_show;
    Texture item_line_show;
    Texture item_stick_show;
    Texture item_wiyer_show;
    Texture item_zender_show;

    Texture scene1dialog;
    Texture scene2dialog;
    Texture scene3dialog;
    Texture scene4dialog;
    Texture scene5dialog;
    Texture scene6dialog;
    Texture scene7dialog;
    Texture scene8dialog;
    Texture scene9dialog;
    Texture scene10dialog;

    Texture map_background;
    Texture map_A;
    Texture map_B;
    Texture map_C;
    Texture map_main;
    Texture map_bunker;

    Texture inventory;
    Texture inventory_under;

    Texture dialogbox;

    Texture skip;

    Texture pet;
};

struct Button {
    RectangleShape sprite;
};

struct Player {
    RectangleShape sprite;
    int speed;
};
struct Pet {
    RectangleShape sprite;
};
const int W_WIDTH = 1600, W_HEIGHT = 900;
const int INVEN_WIDTH = 1600, INVEN_HEIGHT = 900;
const int MAP_WIDTH = 1600, MAP_HEIGHT = 900;
const int DIALOGBOX_WIDTH = 1200, DIALOGBOX_HEIGHT = 300;

bool  item_bolt_bool = false; //전역변수 자제하는 것이 좋음 //근데 이거 말고 방법이 없는데
bool item_speaker_bool = false;
bool item_wiyer_bool = false;
bool item_frism_bool = false;
bool item_piston_bool = false;
bool item_belt_bool = false;
bool item_bridge_bool = false;
bool item_line_bool = false;
bool item_stick_bool = false;
bool item_zender_bool = false;

bool map_A_bool = false;
bool map_B_bool = false;
bool map_C_bool = false;
bool map_main_bool = false;

bool scene_captain_bool = false;

bool draw_firstdialog = true; // 대화창을 그리는지 여부를 나타내는 변수
bool draw_item_found = true;


int main(void) {

    Vector2i mouse_pos;
    int layer = 2;
    int hand = 0;
    int bag = 0;
    int cnt = 0;
    int observing = 0;

    //타이머
    Clock clock;
    Clock ch_timer;
    float interval = 0;
    int count = 0;

    const Time change_time = seconds(0.2f);
    const Time change2_time = seconds(0.4f);
    const Time change3_time = seconds(0.6f);
    const Time change4_time = seconds(0.8f);

    //시점 고정
    View view;
    view.setCenter(Vector2f(W_WIDTH / 2, W_HEIGHT / 2));
    view.setSize(Vector2f(W_WIDTH, W_HEIGHT));

    //사진 로드
    struct Textures tex;

    tex.title_bg.loadFromFile("resource/images/background/title_img.png");
    tex.home_bg.loadFromFile("resource/images/background/map_home.png");

    tex.start_btn_def.loadFromFile("resource/images/btn/title_start_default.png");
    tex.start_btn_sel.loadFromFile("resource/images/btn/title_start_selected.png");
    tex.quit_btn_def.loadFromFile("resource/images/btn/title_exit_default.png");
    tex.quit_btn_sel.loadFromFile("resource/images/btn/title_exit_selected.png");


    tex.main_ch_front_x.loadFromFile("resource/images/character/main_ch/front/ch_f_x.png");
    tex.main_ch_right_x.loadFromFile("resource/images/character/main_ch/right/ch_r_x.png");
    tex.main_ch_left_x.loadFromFile("resource/images/character/main_ch/left/ch_l_x.png");
    tex.main_ch_back_x.loadFromFile("resource/images/character/main_ch/back/ch_b_x.png");

    tex.main_ch_w_f_x_1.loadFromFile("resource/images/character/main_ch/front/f_x_1.png");
    tex.main_ch_w_f_x_2.loadFromFile("resource/images/character/main_ch/front/f_x_2.png");
    tex.main_ch_w_f_x_3.loadFromFile("resource/images/character/main_ch/front/f_x_3.png");
    tex.main_ch_w_f_x_4.loadFromFile("resource/images/character/main_ch/front/f_x_4.png");

    tex.main_ch_w_b_x_1.loadFromFile("resource/images/character/main_ch/back/b_x_1.png");
    tex.main_ch_w_b_x_2.loadFromFile("resource/images/character/main_ch/back/b_x_2.png");


    tex.main_ch_w_l_x_1.loadFromFile("resource/images/character/main_ch/left/l_x_1.png");
    tex.main_ch_w_l_x_2.loadFromFile("resource/images/character/main_ch/left/l_x_2.png");
    tex.main_ch_w_l_x_3.loadFromFile("resource/images/character/main_ch/left/l_x_3.png");
    tex.main_ch_w_l_x_4.loadFromFile("resource/images/character/main_ch/left/l_x_4.png");

    tex.main_ch_w_r_x_1.loadFromFile("resource/images/character/main_ch/right/r_x_1.png");
    tex.main_ch_w_r_x_2.loadFromFile("resource/images/character/main_ch/right/r_x_2.png");
    tex.main_ch_w_r_x_3.loadFromFile("resource/images/character/main_ch/right/r_x_3.png");
    tex.main_ch_w_r_x_4.loadFromFile("resource/images/character/main_ch/right/r_x_4.png");

    tex.main_ch_front_o.loadFromFile("resource/images/character/main_ch/front/ch_f_o.png");
    tex.main_ch_right_o.loadFromFile("resource/images/character/main_ch/right/ch_r_o.png");
    tex.main_ch_left_o.loadFromFile("resource/images/character/main_ch/left/ch_l_o.png");
    tex.main_ch_back_o.loadFromFile("resource/images/character/main_ch/back/ch_b_o.png");

    tex.pet_b.loadFromFile("resource/images/character/pet/ec_b.png");
    tex.pet_f.loadFromFile("resource/images/character/pet/ec_f.png");
    tex.pet_l.loadFromFile("resource/images/character/pet/ec_l.png");
    tex.pet_r.loadFromFile("resource/images/character/pet/ec_r.png");

    //아이템 이미지 (맵에 뜨는 이미지)
    tex.item_frism.loadFromFile("resource/images/item/sml_item_frism.png");
    tex.item_piston.loadFromFile("resource/images/item/sml_item_piston.png");
    tex.item_speaker.loadFromFile("resource/images/item/sml_item_speaker.png");
    tex.item_belt.loadFromFile("resource/images/item/sml_items_belt.png");
    tex.item_bolt.loadFromFile("resource/images/item/sml_items_bolt.png");
    tex.item_bridge.loadFromFile("resource/images/item/sml_items_bridge.png");
    tex.item_line.loadFromFile("resource/images/item/sml_items_line.png");
    tex.item_stick.loadFromFile("resource/images/item/sml_items_stick.png");
    tex.item_wiyer.loadFromFile("resource/images/item/sml_items_wiyer.png");
    tex.item_zender.loadFromFile("resource/images/item/sml_items_zender.png");

    //아이템 이미지 (후광 x)
    tex.item_frism_show.loadFromFile("resource/images/item/item_frism.png");
    tex.item_piston_show.loadFromFile("resource/images/item/item_piston.png");
    tex.item_speaker_show.loadFromFile("resource/images/item/item_speaker.png");
    tex.item_belt_show.loadFromFile("resource/images/item/items_belt.png");
    tex.item_bolt_show.loadFromFile("resource/images/item/items_bolt.png");
    tex.item_bridge_show.loadFromFile("resource/images/item/items_bridge.png");
    tex.item_line_show.loadFromFile("resource/images/item/items_line.png");
    tex.item_stick_show.loadFromFile("resource/images/item/items_stick.png");
    tex.item_wiyer_show.loadFromFile("resource/images/item/items_wiyer.png");
    tex.item_zender_show.loadFromFile("resource/images/item/items_zender.png");

    tex.halo.loadFromFile("resource/images/item/item_halo.png");

    //컷씬 대사
    tex.scene1dialog.loadFromFile("resource/images/text/s1.png");
    tex.scene2dialog.loadFromFile("resource/images/text/s2.png");
    tex.scene3dialog.loadFromFile("resource/images/text/s3.png");
    tex.scene4dialog.loadFromFile("resource/images/text/s4.png");
    tex.scene5dialog.loadFromFile("resource/images/text/s5.png");
    tex.scene6dialog.loadFromFile("resource/images/text/s6.png");
    tex.scene7dialog.loadFromFile("resource/images/text/s7.png");
    tex.scene8dialog.loadFromFile("resource/images/text/s8.png");
    tex.scene9dialog.loadFromFile("resource/images/text/s9.png");
    tex.scene10dialog.loadFromFile("resource/images/text/s10.png");

    //맵
    tex.map_background.loadFromFile("resource/images/ui/map/map_background.png");
    tex.map_A.loadFromFile("resource/images/ui/map/map_A.png");
    tex.map_B.loadFromFile("resource/images/ui/map/map_B.png");
    tex.map_C.loadFromFile("resource/images/ui/map/map_C.png");
    tex.map_main.loadFromFile("resource/images/ui/map/map_main.png");
    tex.map_bunker.loadFromFile("resource/images/ui/map/map_bunker.png");

    //스킵안내버튼
    tex.skip.loadFromFile("resource/images/ui/skip.png");
    //인벤창
    tex.inventory.loadFromFile("resource/images/ui/inventory.png");
    //인벤창 하단
    tex.inventory_under.loadFromFile("resource/images/ui/inventory_under.png");
    //대화창
    tex.dialogbox.loadFromFile("resource/images/ui/dialogbox.png");

    //scene1
    Texture textures[50];
    string filenameFormat1 = "resource/images/scene/scene1/scene1 (%d).png";
    char filename[99];
    for (int i = 0; i <= 49; i++)
    {
        sprintf_s(filename, filenameFormat1.c_str(), i); //파일명을 filename에 저장
        textures[i].loadFromFile(filename);
    }/*
    //scene2
    Texture textures2[49];
    string filenameFormat2 = "resource/images/scene/scene2/scene2 (%d).png";
    for (int i = 0; i <= 48; i++)
    {
       sprintf_s(filename, filenameFormat2.c_str(), i); //파일명을 filename에 저장
       textures2[i].loadFromFile(filename);
    }
    //scene3
    Texture textures3[50];
    string filenameFormat3 = "resource/images/scene/scene3/scene3 (%d).png";
    for (int i = 0; i <= 49; i++)
    {
       sprintf_s(filename, filenameFormat3.c_str(), i); //파일명을 filename에 저장
       textures3[i].loadFromFile(filename);
    }
    //scene4
    Texture textures4[50];
    string filenameFormat4 = "resource/images/scene/scene4/scene4 (%d).png";
    for (int i = 0; i <= 49; i++)
    {
       sprintf_s(filename, filenameFormat4.c_str(), i); //파일명을 filename에 저장
       textures4[i].loadFromFile(filename);
    }
    //scene5
    Texture textures5[50];
    string filenameFormat5 = "resource/images/scene/scene5/scene5 (%d).png";
    for (int i = 0; i <= 49; i++)
    {
       sprintf_s(filename, filenameFormat5.c_str(), i); //파일명을 filename에 저장
       textures5[i].loadFromFile(filename);
    }
    //scene6
    Texture textures6[50];
    string filenameFormat6 = "resource/images/scene/scene6/scene6 (%d).png";
    for (int i = 0; i <= 49; i++)
    {
       sprintf_s(filename, filenameFormat6.c_str(), i); //파일명을 filename에 저장
       textures6[i].loadFromFile(filename);
    }
    //scene7
    Texture textures7[50];
    string filenameFormat7 = "resource/images/scene/scene7/scene7 (%d).png";
    for (int i = 0; i <= 49; i++)
    {
       sprintf_s(filename, filenameFormat7.c_str(), i); //파일명을 filename에 저장
       textures7[i].loadFromFile(filename);
    }
    //scene8
    Texture textures8[45];
    string filenameFormat8 = "resource/images/scene/scene8/scene8 (%d).png";
    for (int i = 0; i <= 44; i++)
    {
       sprintf_s(filename, filenameFormat8.c_str(), i); //파일명을 filename에 저장
       textures8[i].loadFromFile(filename);
    }
    //scene9
    Texture textures9[50];
    string filenameFormat9 = "resource/images/scene/scene9/scene9 (%d).png";
    for (int i = 0; i <= 49; i++)
    {
       sprintf_s(filename, filenameFormat9.c_str(), i); //파일명을 filename에 저장
       textures9[i].loadFromFile(filename);
    }
    //scene10
    Texture textures10[90];
    string filenameFormat10 = "resource/images/scene/scene10/scene10 (%d).png";
    for (int i = 0; i <= 89; i++)
    {
       sprintf_s(filename, filenameFormat10.c_str(), i); //파일명을 filename에 저장
       textures10[i].loadFromFile(filename);

    }*/
    //선장 조우 장면
    Texture scene_captain[90];
    string filenameFormat11 = "resource/images/scene/scene_captain/scene_captain (%d).png";
    for (int i = 0; i <= 89; i++)
    {
        sprintf_s(filename, filenameFormat11.c_str(), i); //파일명을 filename에 저장
        scene_captain[i].loadFromFile(filename);

    }

    RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "Frontier");
    window.setFramerateLimit(60);

    //지도
    Sprite map_background;
    map_background.setTexture(tex.map_background);
    Sprite map_A;
    map_A.setTexture(tex.map_A);
    Sprite map_B;
    map_B.setTexture(tex.map_B);
    Sprite map_C;
    map_C.setTexture(tex.map_C);
    Sprite map_main;
    map_main.setTexture(tex.map_main);
    Sprite map_bunker;
    map_bunker.setTexture(tex.map_bunker);
    //스킵안내
    Sprite skip;
    skip.setTexture(tex.skip);
    skip.setPosition(W_WIDTH - 200, W_HEIGHT - 850);
    //배경
    Sprite title;
    title.setTexture(tex.title_bg);
    title.setPosition(0, 0);
    //컷씬1 대사
    Sprite scene1dialog;
    scene1dialog.setTexture(tex.scene1dialog);
    scene1dialog.setPosition(0, 0);

    //scene1 영상
    Sprite scene1;
    scene1.setTexture(textures[0]);
    scene1.setPosition((window.getSize().x - scene1.getGlobalBounds().width) / 2.0f + 0.5, 67);
    //선장 조우 영상
    Sprite scene_captain_sp;
    scene_captain_sp.setTexture(scene_captain[0]);

    Sprite home;
    home.setTexture(tex.home_bg);
    home.setPosition(600, -700);

    //플레이어
    struct Player player;
    player.sprite.setTexture(&tex.main_ch_front_x);
    player.sprite.setSize(Vector2f(225, 150));
    player.sprite.setPosition(W_WIDTH / 2 - 75, W_HEIGHT / 2 - 75);
    player.speed = 20;

    Sprite pet;
    pet.setTexture(tex.pet_f);
    pet.setScale(0.7f, 0.7f);
    //pet.setPosition(W_WIDTH / 2 - 75, W_HEIGHT / 2 - 75);

    Sprite inventory;
    inventory.setTexture(tex.inventory);

    Sprite inventory_under;
    inventory_under.setTexture(tex.inventory_under);

    //아이템 후광 있는 이미지
    Sprite item_speaker; //큰 아이템
    item_speaker.setTexture(tex.item_speaker);
    item_speaker.setPosition(370, 970);

    Sprite item_piston; //큰 아이템
    item_piston.setTexture(tex.item_piston);
    item_piston.setPosition(670, 970);

    Sprite item_frism; //큰 아이템
    item_frism.setTexture(tex.item_frism);
    item_frism.setPosition(1370, 770);

    Sprite item_bolt;
    item_bolt.setTexture(tex.item_bolt);
    item_bolt.setPosition(170, 770);

    Sprite item_wiyer;
    item_wiyer.setTexture(tex.item_wiyer);
    item_wiyer.setPosition(570, 1370);

    Sprite item_belt;
    item_belt.setTexture(tex.item_belt);
    item_belt.setPosition(170, 1300);

    Sprite item_bridge;
    item_bridge.setTexture(tex.item_bridge);
    item_bridge.setPosition(170, 1500);

    Sprite item_line;
    item_line.setTexture(tex.item_line);
    item_line.setPosition(170, 2000);

    Sprite item_stick;
    item_stick.setTexture(tex.item_stick);
    item_stick.setPosition(170, 1600);

    Sprite item_zender;
    item_zender.setTexture(tex.item_zender);
    item_zender.setPosition(970, 770);

    Sprite halo;
    halo.setTexture(tex.halo);

    //아이템 후광 없는 이미지 
    Sprite item_speaker_show; //큰 아이템
    item_speaker_show.setTexture(tex.item_speaker_show);
    item_speaker_show.setPosition(170, 770);

    Sprite item_frism_show; //큰 아이템
    item_frism_show.setTexture(tex.item_frism_show);
    item_frism_show.setPosition(170, 770);

    Sprite item_piston_show; //큰 아이템
    item_piston_show.setTexture(tex.item_piston_show);
    item_piston_show.setPosition(370, 970);

    Sprite item_bolt_show;
    item_bolt_show.setTexture(tex.item_bolt_show);
    item_bolt_show.setPosition(170, 770);

    Sprite item_wiyer_show;
    item_wiyer_show.setTexture(tex.item_wiyer_show);
    item_wiyer_show.setPosition(170, 770);

    Sprite item_belt_show;
    item_belt_show.setTexture(tex.item_belt_show);
    item_belt_show.setPosition(170, 770);

    Sprite item_bridge_show;
    item_bridge_show.setTexture(tex.item_bridge_show);
    item_bridge_show.setPosition(170, 770);

    Sprite item_line_show;
    item_line_show.setTexture(tex.item_line_show);
    item_line_show.setPosition(170, 770);

    Sprite item_stick_show;
    item_stick_show.setTexture(tex.item_stick_show);
    item_stick_show.setPosition(170, 770);

    Sprite item_zender_show;
    item_zender_show.setTexture(tex.item_zender_show);
    item_zender_show.setPosition(170, 770);

    //폰트불러오기
    Font font;
    font.loadFromFile("./resource/font/IBMPlexSansKR-Medium.ttf");
    if (!font.loadFromFile("./resource/font/IBMPlexSansKR-Medium.ttf"))
    {
        cerr << "Failed to load font file" << endl;
        return 1;
    }
    //컷씬 끝난후 대사
    String firstdialog[] = {
       L"⋯ 이제는 이 곳도 사람이 살 만한 곳이 못 됩니다.",
       L"애초에 섬이 생존가능구역으로 구분된 것부터가 이상했다고요.보셨죠?\n어제도 수위가 10cm는 올랐잖아요.",
       L"과학자님도 하루빨리 여기를 벗어나셔야 해요.\n라디오도 안 터진 지 한 달은 넘은 것 같은데⋯.",
       L"그래요, 오늘은 C구역으로 탐사를 가보는 게 어때요?\n혹시 모르죠, 폐쇄된 항구에 무언가 남아있을지.",
       L"나침반은 고장났으니 제가 길을 안내할게요.",
    };
    //scene2-1(선장 조우) 재생후 
    String captaindialog1[] = {
       L"예상 못 한 손님이군요.\n아직 생존자가 남아있을 줄이야.",
       L"그건 저희가 할 말이거든요! 당신은 대체 누구죠? 방호구도 없이⋯",
       L"그게 중요한가요? 보아하니 이 곳의 상황을 알고 온 건 아닌 것 같은데. ",
       L"저 뒤의 배가 보이시나요?",
       L"한때⋯ 저와 함께하던 배였죠. 지금은 움직일 수 없지만.",
       L"당신도 그 곳으로 가려는 거라면 들뜨셨겠지만, 안타깝게 됐군요.\n지금으로선 딱히 수리할 방도가 없습니다.",
       L"그⋯ 곳?",
       L"둘 다 모르는 눈치로군요.\n하긴, 라디오가 끊긴지 한 달 정도가 되었으니.\n그 정도는 알려드리지요.",
       L"그리 멀지 않은 대륙의 생존가능구역에서\n지구를 벗어나려는 프로젝트를 진행 중이라는 말을 들었습니다.",
       L"그 곳 사람들은, 달로 가려는 거죠. 이 가망 없는 지구를 버리고.",
       L"공식적으로 소식을 들은 사람들은 그리 많지 않지만,\n어디선가 소문이 새어나가면서 꽤 많은 유동인구가 생겼습니다.",
       L"그 때문에 경비를 강화했다던데, 도착해서도 쉽지 않겠지만\n당장 여기서 나갈 방도도 없는 상황이군요.",
       L"당신은 어떻게 그런 정보가 있는 거죠?\n웬만한 소식통은 다 끊겼고,\n이제 여기에 남아있는 사람도 더 없는데.",
       L"이런 상황에서 저만 일방적으로 정보를 제공해야 할 이유는 없습니다만.",
       L"제안을 하나 하죠.",
       L"보시다시피, 저는 장비 상태가 그리 좋지 않아 여기를 나가기 어렵습니다.",
       L"배 수리에 필요한 부품을 모아와주신다면 그 때 당신을 돕도록 하죠.",
       L"⋯ 과학자님, 어떻게 하실래요?",
       L"사실 선택지가 없어 보이긴 하지만⋯",
       L"전 나가고 싶어요. 달로 가는 건 모르겠고, 그냥 여기서 좀 탈출하고 싶어요",
       L"선택지 : 수락한다 / ..."
    };
    //선장 선택지 수락
    String captaindialog1_choice_1[] = {
       L"좋아요. 그럼 필요한 부품을 알려드리겠습니다.",
       //인벤토리 창: 실루엣 추가
       L"인벤토리 창에 실루엣이 추가되었다.",
       L"행운을 빌죠."
    };
    //선장 선택지 ...
    String captaindialog1_choice_2[] = {
       L"내키지 않는 모양이군요?",
       L"아무래도 상관 없습니다. 저는 어떻게 되든 이 배와 함께할 생각이거든요."
    };
    //선장 선택지 ... 후 말검
    String captaindialog1_choice_again[] = {
       L"왜 그러시죠? 마음이 바뀌었나요?",
       L"선택지: 수락한다 / 수락하지 않는다"
    };

    //수락후 부품을 다 찾지 않고 말검
    String item_not_found[] = {
       L"모험에 진척이 없는 모양이군요. 힌트가 필요한가요?",
       L"부품을 찾는 건 당신의 몫입니다.\n저는 이미 상당한 정보를 제공했지만, 당신은 아니죠.",
       L"여기서 나가지도 못 하는 몸인 저에게 무언갈 바라는 것보다\n당신이 직접 부딪혀보는 게 더 도움이 되지 않을까 싶은데."
    };
    //수락후 부품을 다 찾은 후 말검
    String item_found[] = {
       L"정말 다 찾아왔군요.",
       L"이 정도면 상태가 상당히 양호하네요.\n감사를 표합니다. 바로 수리를 시작하죠.",
       //수리 로봇 등장
       L"그동안 더 들어온 정보가 있는데,\n원한다면 수리하는 동안 들려드리겠습니다.",
       L"A.프로젝트?\nB.달?\nC.당신은?\nD.묻지 않는다" //선택지
    };
    //수락후 부품을 다 찾은 후 말검 선택지 프로젝트?
    String item_found_choice_1[] = {
       L"그 달로 가는 프로젝트 말이죠. 그에 대한 정보도 더 들어왔습니다.",
       L"일명 프론티어",
       L"지금 상황에서 보낼 수 있는 인원은 50명...",
       L"하지만 해당 구역의 생존자 수만 70여 명,\n인근에서 접근 중인 것으로 파악되는 인원은 약 100여 명에 달하죠.",
       L"파악되지 않는 레이더 비장착 선박까지 더하면 그 수는 비약적으로 늘어나겠지요.",
       L"그나마 좋은 소식은 이 섬이 그 곳에서 상당히 가까운 편이라는 겁니다.",
       L"잘만 하면 어떻게든 그 50명 안에 들어갈 수 있을지도 모르죠.",
       L"더 원하는 정보가 있나요?"
    };
    //수락후 부품을 다 찾은 후 말검 선택지 달?
    String item_found_choice_2[] = {
       L"아름답지만 척박한 그 곳.\n멸망 이전의 사람들도 그 곳에서의 생활을 꿈꾸었다고들 하죠.",
       L"꽤 오래전의 이야기이지만,\n그 때도 완전히 불가능한 이야기는 아니었으니 지금은 가는 것 자체는 어렵지 않을 겁니다.",
       L"우주선을 개발할 여건이 되느냐가 문제겠죠.",
       L"더 원하는 정보가 있나요?"
    };
    //수락후 부품을 다 찾은 후 말검 선택지 당신은?
    String item_found_choice_3[] = {
       L"글쎄요.",
       L"뭐 다를 게 있을까요? 한때 이 배를 몰던 사람일 뿐입니다.",
       L"굳이 소개하자면⋯ 이 배와 끝까지 함께하며, 운명을 거스르지 않을 생각이라는 것.\n그 정도가 있겠네요.",
       L"더 원하는 정보가 있나요?"
    };
    ///수락후 부품을 다 찾은 후 모든 선택지를 들음
    String item_found_choice_all[] = {
       L"수리가 완료된 것 같군요.",
       L"원한다면 가죠. 그 곳으로."
    };

    while (window.isOpen())

    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2f player_pos = player.sprite.getPosition();
        float time = clock.getElapsedTime().asMilliseconds();
        clock.restart();



        interval += time;

        //  Event event;
        mouse_pos = Mouse::getPosition(window);


        //플레이어 이동
        bool isMoving = false;
        if (Keyboard::isKeyPressed(Keyboard::Left) && layer != 0 && !Keyboard::isKeyPressed(Keyboard::Down) && !Keyboard::isKeyPressed(Keyboard::Up)) { //대각선 이동 방지
            observing = 3;
            pet.setTexture(tex.pet_l);
            pet.setPosition(player_pos.x + 130, player_pos.y - 70);
            view.move(-player.speed, 0);
            std::cout << "Player Position: (" << player.sprite.getPosition().x << ", " << player.sprite.getPosition().y << ")" << std::flush;
            std::cout << "\n" << endl;
            std::cout << "pet Position: (" << pet.getPosition().x << ", " << pet.getPosition().y << ")" << std::flush;
            std::cout << "\n" << endl;
            player.sprite.move(-player.speed, 0);
            isMoving = true;
            if (hand == 0 && isMoving == true) {
                if (ch_timer.getElapsedTime() > change_time) {
                    player.sprite.setTexture(&tex.main_ch_w_l_x_1);
                }
                if (ch_timer.getElapsedTime() > change2_time) {
                    player.sprite.setTexture(&tex.main_ch_w_l_x_2);
                }
                if (ch_timer.getElapsedTime() > change3_time) {
                    player.sprite.setTexture(&tex.main_ch_w_l_x_3);
                }
                if (ch_timer.getElapsedTime() > change4_time) {
                    player.sprite.setTexture(&tex.main_ch_w_l_x_4);
                    ch_timer.restart();
                }
            }
            if (hand == 1 && isMoving == true) {
                if (ch_timer.getElapsedTime() > change_time) {
                    player.sprite.setTexture(&tex.main_ch_left_o);
                }
                if (ch_timer.getElapsedTime() > change2_time) {
                    player.sprite.setTexture(&tex.main_ch_left_o);
                }
                if (ch_timer.getElapsedTime() > change3_time) {
                    player.sprite.setTexture(&tex.main_ch_left_o);
                }
                if (ch_timer.getElapsedTime() > change4_time) {
                    player.sprite.setTexture(&tex.main_ch_left_o);
                    ch_timer.restart();
                }
            }
        }
        else {
            if (layer != 0) {
                pet.setPosition(player_pos.x + 135, player_pos.y - 70);
                switch (observing) {
                case 3:
                    if (hand == 0)
                        player.sprite.setTexture(&tex.main_ch_left_x);
                    if (hand == 1)
                        player.sprite.setTexture(&tex.main_ch_left_o);
                    break;
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Right) && layer != 0 && !Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down)) { //대각선 이동 방지
            observing = 4;
            pet.setTexture(tex.pet_r);
            pet.setPosition(player_pos.x - 540, player_pos.y - 70);
            std::cout << "우측" << endl;
            window.draw(pet);
            view.move(player.speed, 0);
            std::cout << "Player Position: (" << player.sprite.getPosition().x << ", " << player.sprite.getPosition().y << ")" << std::flush;
            std::cout << "\n" << endl;
            std::cout << "pet Position: (" << pet.getPosition().x << ", " << pet.getPosition().y << ")" << std::flush;
            std::cout << "\n" << endl;
            player.sprite.move(player.speed, 0);
            isMoving = true;
            if (hand == 0 && isMoving == true) {
                if (ch_timer.getElapsedTime() > change_time) {
                    player.sprite.setTexture(&tex.main_ch_w_r_x_1);
                }
                if (ch_timer.getElapsedTime() > change2_time) {
                    player.sprite.setTexture(&tex.main_ch_w_r_x_2);
                }
                if (ch_timer.getElapsedTime() > change3_time) {
                    player.sprite.setTexture(&tex.main_ch_w_r_x_3);
                }
                if (ch_timer.getElapsedTime() > change4_time) {
                    player.sprite.setTexture(&tex.main_ch_w_r_x_4);
                    ch_timer.restart();
                }
            }
            if (hand == 1 && isMoving == true) {
                if (ch_timer.getElapsedTime() > change_time) {
                    player.sprite.setTexture(&tex.main_ch_right_o);
                }
                if (ch_timer.getElapsedTime() > change2_time) {
                    player.sprite.setTexture(&tex.main_ch_right_o);
                }
                if (ch_timer.getElapsedTime() > change3_time) {
                    player.sprite.setTexture(&tex.main_ch_right_o);
                }
                if (ch_timer.getElapsedTime() > change4_time) {
                    player.sprite.setTexture(&tex.main_ch_right_o);
                    ch_timer.restart();
                }
            }
        }
        else {
            if (layer != 0) {
                pet.setPosition(player_pos.x - 135, player_pos.y - 70);
                switch (observing) {
                case 4:
                    if (hand == 0)
                        player.sprite.setTexture(&tex.main_ch_right_x);
                    if (hand == 1)
                        player.sprite.setTexture(&tex.main_ch_right_o);
                    break;
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Up) && layer != 0 && !Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right)) { //대각선 이동 방지
            observing = 2;
            pet.setTexture(tex.pet_b);
            pet.setPosition(player_pos.x + 150, player_pos.y - 90);
            window.draw(pet);
            view.move(0, -player.speed);
            std::cout << "Player Position: (" << player.sprite.getPosition().x << ", " << player.sprite.getPosition().y << ")" << std::flush;
            std::cout << "\n" << endl;
            std::cout << "pet Position: (" << pet.getPosition().x << ", " << pet.getPosition().y << ")" << std::flush;
            std::cout << "\n" << endl;
            player.sprite.move(0, -player.speed);
            isMoving = true;
            if (hand == 0 && isMoving == true) {
                if (ch_timer.getElapsedTime() > change_time) {
                    player.sprite.setTexture(&tex.main_ch_w_b_x_1);
                }
                if (ch_timer.getElapsedTime() > change2_time) {
                    player.sprite.setTexture(&tex.main_ch_w_b_x_2);
                }
                if (ch_timer.getElapsedTime() > change3_time) {
                    player.sprite.setTexture(&tex.main_ch_w_b_x_1);
                }
                if (ch_timer.getElapsedTime() > change4_time) {
                    player.sprite.setTexture(&tex.main_ch_w_b_x_2);
                    ch_timer.restart();
                }
            }
            if (hand == 1 && isMoving == true) {
                if (ch_timer.getElapsedTime() > change_time) {
                    player.sprite.setTexture(&tex.main_ch_back_o);
                }
                if (ch_timer.getElapsedTime() > change2_time) {
                    player.sprite.setTexture(&tex.main_ch_back_o);
                }
                if (ch_timer.getElapsedTime() > change3_time) {
                    player.sprite.setTexture(&tex.main_ch_back_o);
                }
                if (ch_timer.getElapsedTime() > change4_time) {
                    player.sprite.setTexture(&tex.main_ch_back_o);
                    ch_timer.restart();
                }
            }
        }
        else {
            if (layer != 0) {
                pet.setPosition(player_pos.x + 150, player_pos.y - 95);
                switch (observing) {
                case 2:
                    if (hand == 0)
                        player.sprite.setTexture(&tex.main_ch_back_x);
                    if (hand == 1)
                        player.sprite.setTexture(&tex.main_ch_back_o);
                    break;
                }
            }
        }


        if (Keyboard::isKeyPressed(Keyboard::Down) && layer != 0 && !Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right)) { //대각선 이동 방지
            observing = 1;
            pet.setTexture(tex.pet_f);
            pet.setPosition(player_pos.x + 140, player_pos.y - 70);
            window.draw(pet);
            view.move(0, player.speed);
            std::cout << "Player Position: (" << player.sprite.getPosition().x << ", " << player.sprite.getPosition().y << ")" << std::flush;
            std::cout << "\n" << endl;
            std::cout << "pet Position: (" << pet.getPosition().x << ", " << pet.getPosition().y << ")" << std::flush;
            std::cout << "\n" << endl;
            player.sprite.move(0, player.speed);
            isMoving = true;
            if (hand == 0 && isMoving == true) {
                if (ch_timer.getElapsedTime() > change_time) {
                    player.sprite.setTexture(&tex.main_ch_w_f_x_1);
                }
                if (ch_timer.getElapsedTime() > change2_time) {
                    player.sprite.setTexture(&tex.main_ch_w_f_x_2);
                }
                if (ch_timer.getElapsedTime() > change3_time) {
                    player.sprite.setTexture(&tex.main_ch_w_f_x_3);
                }
                if (ch_timer.getElapsedTime() > change4_time) {
                    player.sprite.setTexture(&tex.main_ch_w_f_x_4);
                    ch_timer.restart();
                }
            }
            if (hand == 1 && isMoving == true) {
                if (ch_timer.getElapsedTime() > change_time) {
                    player.sprite.setTexture(&tex.main_ch_front_o);
                }
                if (ch_timer.getElapsedTime() > change2_time) {
                    player.sprite.setTexture(&tex.main_ch_front_o);
                }
                if (ch_timer.getElapsedTime() > change3_time) {
                    player.sprite.setTexture(&tex.main_ch_front_o);
                }
                if (ch_timer.getElapsedTime() > change4_time) {
                    player.sprite.setTexture(&tex.main_ch_front_o);
                    ch_timer.restart();
                }
            }
        }
        else {
            if (layer != 0) {
                pet.setPosition(player_pos.x + 140, player_pos.y - 67);
                switch (observing) {
                case 1:
                    if (hand == 0)
                        player.sprite.setTexture(&tex.main_ch_front_x);
                    if (hand == 1)
                        player.sprite.setTexture(&tex.main_ch_front_o);
                    break;
                }
            }
        }

        while (window.pollEvent(event)) {   //윈도우 창 닫기
            switch (event.type) {
            case Event::Closed:
                window.close();
                break;
            }
        }
        window.setView(view);
        window.clear(Color::Black);
        if (layer == 0) {
            window.draw(title);

            //시작 버튼
            struct Button start_button;
            start_button.sprite.setTexture(&tex.start_btn_sel);
            start_button.sprite.setSize(Vector2f(267, 120));
            start_button.sprite.setPosition(W_WIDTH / 2 - 150, 450);
            if (start_button.sprite.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
                start_button.sprite.setTexture(&tex.start_btn_def);
            }
            if (start_button.sprite.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y) && Mouse::isButtonPressed(Mouse::Left))
                layer = 1;

            //종료 버튼
            struct Button quit_button;
            quit_button.sprite.setTexture(&tex.quit_btn_sel);
            quit_button.sprite.setSize(Vector2f(267, 120));
            quit_button.sprite.setPosition(W_WIDTH / 2 - 150, 610);
            if (quit_button.sprite.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
                quit_button.sprite.setTexture(&tex.quit_btn_def);
            }
            if (quit_button.sprite.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y) && Mouse::isButtonPressed(Mouse::Left))
                return 0;

            window.draw(start_button.sprite);
            window.draw(quit_button.sprite);
        }

        if (layer == 2) {
            window.draw(home);
            window.draw(player.sprite);
            window.draw(pet);
            //   std::cout << "플레이어,펫" << endl;
        }
        /*
        //컷씬 출력
        Clock clock;
        Time elapsed = Time::Zero;
        Time frameTime = seconds(0.083f);
        int sceneindex = 1;
        while (layer == 1 && sceneindex < 11) //씬1~10
        {

           int imgcountmax = 50;
           switch (sceneindex)
           {
           case 2:
              imgcountmax = 49;
              break;
           case 8:
              imgcountmax = 45;
              break;
           case 10:
              imgcountmax = 90;
              break;
           default:
              imgcountmax = 50;
              break;
           }

           int currentTextureIndex = 0;

           while (imgcountmax > currentTextureIndex) {
              elapsed += clock.restart();
              while (window.pollEvent(event)) {
                 switch (event.type) {
                 case Event::Closed:
                    window.close();
                    break;
                 }
              }
              if (elapsed >= frameTime) {

                 if (Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    layer = 2;
                    break;
                 }

                 switch (sceneindex) {
                 case 1:
                    scene1.setTexture(textures[currentTextureIndex]);
                    scene1dialog.setTexture(tex.scene1dialog);
                    break;
                 case 2:
                    scene1.setTexture(textures2[currentTextureIndex]);
                    scene1dialog.setTexture(tex.scene2dialog);
                    break;
                 case 3:
                    scene1.setTexture(textures3[currentTextureIndex]);
                    scene1dialog.setTexture(tex.scene3dialog);
                    break;
                 case 4:
                    scene1.setTexture(textures4[currentTextureIndex]);
                    scene1dialog.setTexture(tex.scene4dialog);
                    break;
                 case 5:
                    scene1.setTexture(textures5[currentTextureIndex]);
                    scene1dialog.setTexture(tex.scene5dialog);
                    break;
                 case 6:
                    scene1.setTexture(textures6[currentTextureIndex]);
                    scene1dialog.setTexture(tex.scene6dialog);
                    break;
                 case 7:
                    scene1.setTexture(textures7[currentTextureIndex]);
                    scene1dialog.setTexture(tex.scene7dialog);
                    break;
                 case 8:
                    scene1.setTexture(textures8[currentTextureIndex]);
                    scene1dialog.setTexture(tex.scene8dialog);
                    break;
                 case 9:
                    scene1.setTexture(textures9[currentTextureIndex]);
                    scene1dialog.setTexture(tex.scene9dialog);
                    break;
                 case 10:
                    scene1.setTexture(textures10[currentTextureIndex]);
                    scene1dialog.setTexture(tex.scene10dialog);
                    break;
                 default:
                    break;
                 }

                 currentTextureIndex++;
                 std::cout << currentTextureIndex << endl;
                 elapsed -= frameTime;
              }

              window.draw(scene1dialog);
              window.draw(skip);
              window.draw(scene1);
              window.display();

           }

           std::cout << sceneindex << endl;
           sceneindex++;

           if (sceneindex > 10) {
              layer = 2;
              break;
           }
        }*/

        /*if (player_pos.x > 1000 && player_pos.x < 1300 && player_pos.y > 300 && player_pos.y < 500); {
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                player.speed = 20;
            }
        }*/

        //선장 조우 영상
        //layer == 2로 해야하는ㄷ ㅔ 임시로 바꿈
        if (layer == 9 && (player_pos.x > 1000 && player_pos.x < 1300) && (player_pos.y > 300 && player_pos.y < 500) && scene_captain_bool == false) {
            scene_captain_sp.setPosition((player_pos.x + 1067 / 2 + 75 - 1067) + 15, player_pos.y + 600 / 2 - (600 - 75)); //중앙
            int currentTextureIndex = 0;
            Clock clock;
            Time elapsed = Time::Zero;
            Time frameTime = seconds(0.083f);

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                elapsed += clock.restart();

                if (elapsed >= frameTime) {
                    if (currentTextureIndex >= 90) {
                        scene_captain_bool = true;
                        //window.close();
                        break;
                    }

                    scene_captain_sp.setTexture(scene_captain[currentTextureIndex]);
                    currentTextureIndex++;
                    elapsed -= frameTime;
                }

                window.clear();
                window.draw(scene_captain_sp);
                window.display();
            }
        }

        //아이템 그리기
        if (layer == 2 && item_bolt_bool == false) {
            window.draw(item_bolt);
            if (player.sprite.getGlobalBounds().intersects(item_bolt.getGlobalBounds())) {
                item_bolt_bool = true;
                //   halo.setPosition(player_pos.x + 1000 / 2 + 75 - 1000, player_pos.y + 1000 / 2 - (1000 - 75));
                //   window.draw(halo);
            }
        }
        if (layer == 2 && item_speaker_bool == false) {
            window.draw(item_speaker);
            if (player.sprite.getGlobalBounds().intersects(item_speaker.getGlobalBounds())) {
                item_speaker_bool = true;
            }
        }
        if (layer == 2 && item_wiyer_bool == false) {
            window.draw(item_wiyer);
            if (player.sprite.getGlobalBounds().intersects(item_wiyer.getGlobalBounds())) {
                item_wiyer_bool = true;
            }
        }
        if (layer == 2 && item_frism_bool == false) {
            window.draw(item_frism);
            if (player.sprite.getGlobalBounds().intersects(item_frism.getGlobalBounds())) {

                item_frism_bool = true;
            }
        }
        if (layer == 2 && item_piston_bool == false) {
            window.draw(item_piston);
            if (player.sprite.getGlobalBounds().intersects(item_piston.getGlobalBounds())) {
                item_piston_bool = true;
            }
        }
        if (layer == 2 && item_belt_bool == false) {
            window.draw(item_belt);
            if (player.sprite.getGlobalBounds().intersects(item_belt.getGlobalBounds())) {
                item_belt_bool = true;
            }
        }
        if (layer == 2 && item_bridge_bool == false) {
            window.draw(item_bridge);
            if (player.sprite.getGlobalBounds().intersects(item_bridge.getGlobalBounds())) {
                item_bridge_bool = true;
            }
        }
        if (layer == 2 && item_line_bool == false) {
            window.draw(item_line);
            if (player.sprite.getGlobalBounds().intersects(item_line.getGlobalBounds())) {
                item_line_bool = true;
            }
        }
        if (layer == 2 && item_stick_bool == false) {
            window.draw(item_stick);
            if (player.sprite.getGlobalBounds().intersects(item_stick.getGlobalBounds())) {
                item_stick_bool = true;
            }
        }
        if (layer == 2 && item_zender_bool == false) {
            window.draw(item_zender);
            if (player.sprite.getGlobalBounds().intersects(item_zender.getGlobalBounds())) {
                item_zender_bool = true;
            }
        }
        //하단 인벤
        if (layer == 2) {
            if (isMoving == false && observing == 0) {
                inventory_under.setPosition(player_pos.x, player_pos.y + 60);
            }
            //3=L  1== DOWN 4==R 2==UP
            if (isMoving == true && observing == 3) {
                inventory_under.setPosition(player_pos.x - 20, player_pos.y + 60);
            }
            if (isMoving == true && observing == 2) {
                inventory_under.setPosition(player_pos.x, player_pos.y + 40);
            }
            if (isMoving == true && observing == 1) {
                inventory_under.setPosition(player_pos.x, player_pos.y + 80);
            }
            if (isMoving == true && observing == 4) {
                inventory_under.setPosition(player_pos.x + 20, player_pos.y + 60);
            }

            window.draw(inventory_under);
            //std::cout << "인벤x : "<<inventory_under.getPosition().x << endl;
            //std::cout << "인벤y : " << inventory_under.getPosition().y << endl;
            //std::cout << "\n" << endl;
        }
        sf::Vector2f inventory_under_pos = inventory_under.getPosition();
        if (item_speaker_bool == true) {
            item_speaker_show.setPosition(inventory_under_pos.x + 410, inventory_under_pos.y + 160);
            item_speaker_show.setScale(0.17f, 0.17f);
            //크기를 700에서 120으로 줄이기
            window.draw(item_speaker_show);
        }
        if (item_frism_bool == true) {
            item_frism_show.setPosition(inventory_under_pos.x + 560, inventory_under_pos.y + 160);
            item_frism_show.setScale(0.17f, 0.17f);
            window.draw(item_frism_show);
        }
        if (item_piston_bool == true) {
            item_piston_show.setPosition(inventory_under_pos.x + 720, inventory_under_pos.y + 160);
            item_piston_show.setScale(0.17f, 0.17f);
            window.draw(item_piston_show);
        }
        if (item_bolt_bool == true) {
            item_bolt_show.setPosition(inventory_under_pos.x + 75, inventory_under_pos.y + 360);
            item_bolt_show.setScale(0.11f, 0.11f);
            //크기를 700에서 80으로 줄이기
            window.draw(item_bolt_show);
        }
        if (item_belt_bool == true) {
            item_belt_show.setPosition(inventory_under_pos.x + 200, inventory_under_pos.y + 360);
            item_belt_show.setScale(0.11f, 0.11f);
            window.draw(item_belt_show);
        }
        if (item_bridge_bool == true) {
            item_bridge_show.setPosition(inventory_under_pos.x + 310, inventory_under_pos.y + 360);
            item_bridge_show.setScale(0.11f, 0.11f);
            window.draw(item_bridge_show);
        }
        if (item_line_bool == true) {
            item_line_show.setPosition(inventory_under_pos.x + 420, inventory_under_pos.y + 360);
            item_line_show.setScale(0.11f, 0.11f);
            window.draw(item_line_show);
        }
        if (item_stick_bool == true) {
            item_stick_show.setPosition(inventory_under_pos.x + 530, inventory_under_pos.y + 360);
            item_stick_show.setScale(0.11f, 0.11f);
            window.draw(item_stick_show);
        }
        if (item_wiyer_bool == true) {
            item_wiyer_show.setPosition(inventory_under_pos.x + 650, inventory_under_pos.y + 360);
            item_wiyer_show.setScale(0.11f, 0.11f);
            window.draw(item_wiyer_show);
        }
        if (item_zender_bool == true) {
            item_zender_show.setPosition(inventory_under_pos.x + 760, inventory_under_pos.y + 360);
            item_zender_show.setScale(0.11f, 0.11f);
            window.draw(item_zender_show);
        }
        //인벤토리 그리기
        if (layer != 0 && isMoving == false) {
            inventory.setPosition(player_pos.x + W_WIDTH / 2 + 75 - INVEN_WIDTH, player_pos.y + W_HEIGHT / 2 - (INVEN_HEIGHT - 75));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                sf::Clock clock;
                bool drawInventory = true;
                while (window.isOpen()) {
                    window.draw(inventory);
                    if (item_frism_bool == true) {
                        item_frism_show.setScale(0.17f, 0.17f);
                        item_frism_show.setPosition(player_pos.x - 290, player_pos.y - 200);
                        window.draw(item_frism_show);
                    }
                    if (item_piston_bool == true) {
                        item_piston_show.setScale(0.17f, 0.17f);
                        item_piston_show.setPosition(player_pos.x - 390, player_pos.y + 10);
                        window.draw(item_piston_show);
                    }
                    if (item_speaker_bool == true) {
                        item_speaker_show.setScale(0.17f, 0.17f);
                        item_speaker_show.setPosition(player_pos.x - 200, player_pos.y + 10);
                        window.draw(item_speaker_show);
                    }
                    if (item_bolt_bool == true) {
                        item_bolt_show.setScale(0.17f, 0.17f);
                        item_bolt_show.setPosition(player_pos.x + 40, player_pos.y - 80);
                        window.draw(item_bolt_show);
                    }
                    if (item_wiyer_bool == true) {
                        item_wiyer_show.setScale(0.17f, 0.17f);
                        item_wiyer_show.setPosition(player_pos.x + 180, player_pos.y - 80);
                        window.draw(item_wiyer_show);
                    }
                    if (item_belt_bool == true) {
                        item_belt_show.setScale(0.17f, 0.17f);
                        item_belt_show.setPosition(player_pos.x + 320, player_pos.y - 80);
                        window.draw(item_belt_show);
                    }
                    if (item_bridge_bool == true) {
                        item_bridge_show.setScale(0.17f, 0.17f);
                        item_bridge_show.setPosition(player_pos.x + 460, player_pos.y - 80);
                        window.draw(item_bridge_show);
                    }
                    if (item_line_bool == true) {
                        item_line_show.setScale(0.17f, 0.17f);
                        item_line_show.setPosition(player_pos.x + 110, player_pos.y + 30);
                        window.draw(item_line_show);
                    }
                    if (item_stick_bool == true) {
                        item_stick_show.setScale(0.17f, 0.17f);
                        item_stick_show.setPosition(player_pos.x + 250, player_pos.y + 30);
                        window.draw(item_stick_show);
                    }
                    if (item_zender_bool == true) {
                        item_zender_show.setScale(0.17f, 0.17f);
                        item_zender_show.setPosition(player_pos.x + 390, player_pos.y + 30);
                        window.draw(item_zender_show);
                    }

                    window.display();

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && clock.getElapsedTime().asSeconds() > 0.2f) {
                        drawInventory = !drawInventory;
                        clock.restart();
                    }

                    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !drawInventory) {
                        break;
                    }
                }
            }
        }

        //지도 띄우기
        map_background.setPosition(player_pos.x + W_WIDTH / 2 + 75 - MAP_WIDTH, player_pos.y + W_HEIGHT / 2 - (MAP_HEIGHT - 75));
        map_A.setPosition(player_pos.x + W_WIDTH / 2 + 75 - MAP_WIDTH, player_pos.y + W_HEIGHT / 2 - (MAP_HEIGHT - 75));
        map_B.setPosition(player_pos.x + W_WIDTH / 2 + 75 - MAP_WIDTH, player_pos.y + W_HEIGHT / 2 - (MAP_HEIGHT - 75));
        map_C.setPosition(player_pos.x + W_WIDTH / 2 + 75 - MAP_WIDTH, player_pos.y + W_HEIGHT / 2 - (MAP_HEIGHT - 75));
        map_main.setPosition(player_pos.x + W_WIDTH / 2 + 75 - MAP_WIDTH, player_pos.y + W_HEIGHT / 2 - (MAP_HEIGHT - 75));
        map_bunker.setPosition(player_pos.x + W_WIDTH / 2 + 75 - MAP_WIDTH, player_pos.y + W_HEIGHT / 2 - (MAP_HEIGHT - 75));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && layer == 2 && isMoving == false) {
            sf::Clock clock;
            bool drawmap = true;

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            while (window.isOpen()) {
                window.draw(map_background);
                window.draw(map_bunker);
                window.draw(map_A);
                window.display();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && clock.getElapsedTime().asSeconds() > 0.2f) {
                    drawmap = !drawmap;
                    clock.restart();
                }

                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::M) && !drawmap) {
                    break;
                }
            }
        }
        //대화창
        Sprite dialogbox;
        dialogbox.setTexture(tex.dialogbox);
        dialogbox.setPosition((player_pos.x + W_WIDTH / 2 - DIALOGBOX_WIDTH - 100),
            player_pos.y + W_HEIGHT / 2 - DIALOGBOX_HEIGHT);

        // 텍스트 출력용 객체 생성
        Text text;
        text.setFont(font);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Blue);
        text.setPosition((player_pos.x + W_WIDTH / 2 - DIALOGBOX_WIDTH),
            player_pos.y + W_HEIGHT / 2 - DIALOGBOX_HEIGHT + 70);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (layer == 2 && (player_pos.x > 200 && player_pos.x < 400) &&
            (player_pos.y > 300 && player_pos.y < 500) && event.key.code == Keyboard::Space && draw_firstdialog == true && isMoving == false) {
            int dialogIndex = 0; // 대화 인덱스
            bool isDialogFinished = false; // 대화가 끝났는지 여부를 나타내는 변수
            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                    else if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Space && dialogIndex < 5) {
                            isDialogFinished = true;
                        }
                    }
                }
                // 대화가 끝났으면 다음 대화 인덱스로 넘어감
                if (isDialogFinished) {
                    dialogIndex++;
                    isDialogFinished = false;
                }
                // 대화창 그리기
                if (draw_firstdialog && dialogIndex < 5) {
                    window.draw(dialogbox);
                    text.setString(firstdialog[dialogIndex]);
                    window.draw(text);
                    window.display();
                }
                // 대화가 모두 끝났을 경우 대화창 그리기 중단
                if (dialogIndex == 5 && Keyboard::Space) {
                    draw_firstdialog = false;
                    break;
                }
            }
        }
        //if (layer == 2 && (player_pos.x > 700 && player_pos.x < 750) &&
        //   (player_pos.y < -90 && player_pos.y > -300) && event.key.code == Keyboard::Space && draw_item_found == true && isMoving == false) {
        //   int dialogIndex = 0; // 대화 인덱스
        //   bool isDialogFinished = false; // 대화가 끝났는지 여부를 나타내는 변수
        //   while (window.isOpen()) {
        //      sf::Event event;
        //      while (window.pollEvent(event)) {
        //         if (event.type == sf::Event::Closed) {
        //            window.close();
        //         }
        //         else if (event.type == sf::Event::KeyPressed) {
        //            if (event.key.code == sf::Keyboard::Space && dialogIndex < 4) {
        //               isDialogFinished = true;
        //            }
        //         }
        //      }
        //      // 대화가 끝났으면 다음 대화 인덱스로 넘어감
        //      if (isDialogFinished) {
        //         dialogIndex++;
        //         isDialogFinished = false;
        //      }
        //      // 대화창 그리기
        //      if (draw_firstdialog && dialogIndex < 4) {
        //         window.draw(dialogbox);
        //         text.setString(item_found[dialogIndex]);
        //         window.draw(text);
        //         window.display();
        //      }
        //      // 대화가 모두 끝났을 경우 대화창 그리기 중단
        //      if (dialogIndex == 4 && Keyboard::Space) {
        //         draw_item_found = false;
        //         break;
        //      }
        //   }
        //}
        window.display();
    }
}