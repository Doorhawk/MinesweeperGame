#include "WindowManager.h"
#include <sstream>
#include <iostream>
#include <string>
using namespace sf;

WindowManager::WindowManager() {
    
    tileSize = 20;
    betweenTileSize = 1;
    edgeSize = 50;
    bombDensity = 10;
    gameDifficult = 0;
    sceneNum = 0;
    isEnableDemonicLevel = false;
    soundPlyed = false;
    width = 400;
    height = 400;

    game.setNewSize(1, 1);
    gameSizeX = game.getGameSize().x;
    gameSizeY = game.getGameSize().y;
    createWindow(width, height);

	window.setVerticalSyncEnabled(true);
    if (!font.loadFromFile("resources/font/Industry.ttf")) {
        std::cout << "font not founded";
    }

    audio.setSoundVolume(90);
    
}

void WindowManager::updateWindow() {


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            controlButtons(event);
        }
        
        drawFrame();
        
    }
}

void WindowManager::changeSceen() {
    if (sceneNum) {
        width = 400;
        height = 400;
        createWindow(width, height);
        sceneNum = 0;
    }
    else {
        sceneNum = 1;
        changeSize(0,false);
    }
}
void WindowManager::changeTileSise(int ch) {
    if(!isEnableDemonicLevel)
    {
        tileSize += ch * 2;
        if (tileSize < 1)
            tileSize = 1;
        changeSize(0, true);
        restartGame();
    }
}
void WindowManager::drawGame() {
    Color backCol(100, 100, 100);
    Color tileCol(180, 180, 180);
    Color tileOpenCol(230, 230, 230);
    Color textCol(30, 30, 30);
    Color markerCol(200, 0, 0);

    window.clear(backCol);


    // draw tile
    int m1IndentX = 5;
    int m1IndentY = 5;
    int m2IndentX = 5;
    int m2IndentY = 5;
    std::vector<std::vector<Tile>> tiles = game.getTiles();
    RectangleShape rec;
    RectangleShape marker1;
    marker1.setFillColor(markerCol);
    CircleShape marker2(1, 3);
    marker2.setFillColor(markerCol);
    CircleShape bom(1.f);
    bom.setFillColor(backCol);


    Text num;
    num.setFont(font);
    num.setFillColor(textCol);
    num.setCharacterSize(tileSize / 20. * 20);
    for (int i = 0; i < gameSizeX; i++) {
        for (int j = 0; j < gameSizeY; j++) {
            rec.setSize(Vector2f(tileSize, tileSize));
            rec.setPosition((i + 1) * betweenTileSize + i * tileSize, (j + 2) * betweenTileSize + j * tileSize + edgeSize);
            rec.setFillColor(tileCol);

            switch (tiles[i][j].getStatus())
            {
            case opened:
                rec.setFillColor(tileOpenCol);
                if ((tiles[i][j].getBombAway() > 0)) {

                    int number = tiles[i][j].getBombAway();
                    num.setString(std::to_string(number));

                    int numIndentX = tileSize / 20. * 4;
                    if (tiles[i][j].getBombAway() == 1)
                        numIndentX = tileSize / 20. * 6;

                    switch (tiles[i][j].getBombAway())
                    {
                    case 1:
                        num.setFillColor(Color(0, 0, 200));
                        break;
                    case 2:
                        num.setFillColor(Color(0, 120, 0));
                        break;
                    case 3:
                        num.setFillColor(Color(200, 0, 0));
                        break;
                    case 4:
                        num.setFillColor(Color(100, 0, 100));
                        break;
                    case 5:
                        num.setFillColor(Color(0, 100, 100));
                        break;
                    case 6:
                        num.setFillColor(Color(100, 100, 0));
                        break;
                    case 7:
                        num.setFillColor(Color(100, 50, 50));
                        break;
                    default:
                        num.setFillColor(Color(50, 100, 0));
                        break;
                    }


                    int numIndentY = tileSize / 20. * ( - 2);
                    num.setPosition((i + 1) * betweenTileSize + i * tileSize + numIndentX, (j + 2) * betweenTileSize + j * tileSize + edgeSize + numIndentY);
                }
                break;
            case closed:
                break;
            case markered:
                m1IndentX = tileSize/20.*6;
                m1IndentY = tileSize / 20. * 4;
                m2IndentX = tileSize / 20. * 16;
                m2IndentY = tileSize / 20. * 4;
                marker1.setSize(Vector2f( 1./15*tileSize+2/3., tileSize / 20. * 14));
                marker2.setRadius(tileSize / 20. * 6.f);
                marker2.setRotation(90);
                marker1.setPosition((i + 1) * betweenTileSize + i * tileSize + m1IndentX, (j + 2) * betweenTileSize + j * tileSize + edgeSize + m1IndentY);
                marker2.setPosition((i + 1) * betweenTileSize + i * tileSize + m2IndentX, (j + 2) * betweenTileSize + j * tileSize + edgeSize + m2IndentY);
                
                break;
            case blownuped:
                bom.setRadius(tileSize / 20. * 6.f);
                bom.setFillColor(Color(0, 0, 0));
                bom.setPosition((i + 1) * betweenTileSize + i * tileSize + tileSize / 20. * 4, (j + 2) * betweenTileSize + j * tileSize + edgeSize + tileSize / 20. * 4);
                rec.setFillColor(Color(220, 0, 0));
                
                break;
            default:
                break;
            }

            window.draw(rec);
            window.draw(num);
            window.draw(marker1);
            window.draw(marker2);
            window.draw(bom);
        }
    }

    //draw edge
    rec.setSize(Vector2f(width - 2 * betweenTileSize, edgeSize));
    rec.setFillColor(tileCol);
    rec.setPosition(betweenTileSize, betweenTileSize);
    window.draw(rec);


    Text text;
    text.setFont(font);
    text.setFillColor(textCol);
    text.setCharacterSize(20);

    //draw time
    int time = game.getGameTime();
    int correction = 0;
    if (time >= 10&&game.getGameSize().x<7)
        correction = 5;
    if (time >= 100 && game.getGameSize().x < 7)
        correction = 10;
    text.setString(std::to_string(time));
    text.setPosition(20-correction, edgeSize / 4 + betweenTileSize);
    window.draw(text);

    //draw flagSum
    int flags = game.getFlagSum();
    text.setString(std::to_string(flags));
    text.setPosition(width - 20 - width / 15, edgeSize / 4 + betweenTileSize);
    window.draw(text);

    // basicBotume
    rec.setSize(Vector2f(30, 30));
    rec.setFillColor(Color(100, 100, 100));
    rec.setPosition(width / 2 - 15, 12);
    window.draw(rec);

    rec.setSize(Vector2f(28, 28));
    rec.setFillColor(Color(200, 200, 200));
    if (game.getIsSeccess()) {
        rec.setFillColor(Color(0, 200, 0));
    }
    else if (game.getIsBad()) {
        rec.setFillColor(Color(200, 0, 0));
    }
    rec.setPosition(width / 2 - 14, 13);
    window.draw(rec);


    window.display();
}
void WindowManager::drawMainScreen() {
    using namespace std;
    
    Color clearCol;
    Color shape1Col;
    Color shape2Col;

    if(!isEnableDemonicLevel){
        clearCol=Color(180 - bombDensity / 2, 180 - bombDensity / 2, 180 - bombDensity / 2);
        shape1Col = Color(150, 0, 0, bombDensity / 100. * 150 + 100);
        shape2Col = Color(255, 0, 0, bombDensity / 100. * 150 + 100);
    }
    else {
        clearCol = Color::Red;
        shape1Col = Color::Green;
        shape2Col = Color::Yellow;
    }


    window.clear(clearCol);
                    
    Text text;
    text.setFont(font);
    text.setFillColor(Color(30,30,30));
    text.setCharacterSize(23);
    text.setPosition(width / 8, height / 9);
    
    string menuText;
    stringstream ss,st;
    if (!isEnableDemonicLevel) {
        ss << "Play/Menu - Space\n"
            << "Restart - R\n\n"
            << "Change difficult - Left Right\n"
            << "Change bomb num - Up Down\n\n"
            << "                   Game size = < " << gameSizeX << ", " << gameSizeY << " >\n"
            << "                       Bomb % = < " << bombDensity << " >";
        st << "press - D ;)";
    }
    else {
        vector<char> messаgе;
        for (int i = 150; i < 280; i++) {
            if (i % 20==0) {
                messаgе.push_back('\n');
            }
            messаgе.push_back(char(i));
        }
        messаgе.push_back('\0');
        string str(messаgе.begin(), messаgе.end());
        //ss<<"Are_you+=SSssure????\n"<< str << " tRy t0 PlАy\n                 BomB %  _- " << bombDensity << " -+_";
        ss << "Are_you+=SSssure????\n" << str << " tRy t0 PlАy\n                 BomB _- 99,997...% -+_";
        text.rotate(5);
    }

    
    menuText = ss.str();
    text.setString(menuText);
    window.draw(text);

    if(gameDifficult==6){
        menuText = st.str();
        text.setString(menuText);
        text.setPosition(5 * width / 10, 8 * height / 10);
        text.setCharacterSize(12);
        text.rotate(70);
        window.draw(text);
    }


    CircleShape shape(10);
    float r = 1;

    r = 120+gameDifficult*10;
    shape.setRadius(r);
    shape.setPosition(-r / 2 - 25, height - r + 2);
    shape.setFillColor(shape1Col);
    window.draw(shape);

    r = 100+ gameDifficult * 10;
    shape.setRadius(r);
    shape.setPosition(-r / 2-15, height - r+2);
    shape.setFillColor(shape2Col);
    window.draw(shape);

    r = 70+ gameDifficult * 10;
    shape.setRadius(r);
    shape.setFillColor(Color::Black);
    shape.setPosition(-r/2, height-r);
    window.draw(shape);

    RectangleShape rec(Vector2f(95 + gameDifficult * 11, 15+gameDifficult));
    rec.setFillColor(Color::Black);
    rec.setPosition(25 + gameDifficult*5, height-10);
    window.draw(rec);
    rec.rotate(-45);
    rec.setSize(Vector2f(85 + gameDifficult * 11, 15+gameDifficult));
    window.draw(rec);
    rec.setSize(Vector2f(75 + gameDifficult * 11, 15 + gameDifficult));
    rec.rotate(-45);
    window.draw(rec);

   

    window.display();
}
void WindowManager::changeSize(int change, bool res = true) {
    gameDifficult += change;
    if (gameDifficult < 0 || gameDifficult > 6) {
        gameDifficult = 0;
    }
        // при переходе между сценами игра не рестертится
    if (isEnableDemonicLevel) {
        gameDifficult = -1;
    }
    if (res) {
        switch (gameDifficult)
        {
        case -1:
            game.setNewSize(300, 150);
            tileSize = 5;
            break;
        case 0:
            game.setNewSize(1, 1);
            break;
        case 1:
            game.setNewSize(6, 1);
            break;
        case 2:
            game.setNewSize(6, 6);
            break;
        case 3:
            game.setNewSize(10, 8);
            break;
        case 4:
            game.setNewSize(20, 15);
            break;
        case 5:
            game.setNewSize(30, 20);
            break;
        case 6:
            game.setNewSize(40, 40);
            break;
        default:
            game.setNewSize(6, 6);
            break;
        }

        restartGame();
    }
    gameSizeX = game.getGameSize().x;
    gameSizeY = game.getGameSize().y;
    
        // из главного экрана можно менять размер поля но новое окно с полем не откроется
    if (sceneNum == 1) {
        width = tileSize * gameSizeX + (gameSizeX + 1) * betweenTileSize;
        if (width < 120) {
            width = 120;
        }
        height = tileSize * gameSizeY + (gameSizeY + 1) * betweenTileSize + edgeSize + betweenTileSize;
        createWindow(width, height);
    }
    
}
void WindowManager::changeBombSum(int change) {
    bombDensity += 1 * change;
    if (bombDensity >25) {
        bombDensity = 25;
    }
    else if (bombDensity < 0) {
        bombDensity = 0;
    }

    // в самом слжном уровне програма крашится при маленько количестве бомб,
    // думаю это потому что функция открытия свободных ячеек реализовна через рекурсию

    if (isEnableDemonicLevel) {
        bombDensity = 100;
    }
    game.setBombDensity(bombDensity/100.);
    restartGame();
}
void WindowManager::drawFrame() {

    switch (sceneNum)
    {
    case 0:
        drawMainScreen();
        break;
    case 1:
        drawGame();
        break;
    default:
        break;
    }
    
    
}
void WindowManager::controlButtons(Event ev) {

    if (ev.type == Event::KeyPressed){
        
        

        if (ev.key.code == Keyboard::R) {
            restartGame(); audio.playSound(buttonS);
        }
        if (ev.key.code == Keyboard::Left) {
            changeSize(-1); audio.playSound(buttonS);
        }
        if (ev.key.code == Keyboard::Right) {
            changeSize(1); audio.playSound(buttonS);
        }
        if (ev.key.code == Keyboard::Up) {
            changeBombSum(1); audio.playSound(buttonS);
        }
        if (ev.key.code == Keyboard::Down) {
            changeBombSum(-1); audio.playSound(buttonS);
        }
        if (ev.key.code == Keyboard::Space) {
            changeSceen(); audio.playSound(buttonS);
        }
        if (ev.key.code == Keyboard::D) {
            enableDemonicLevel(); audio.playSound(buttonS);
        }
        if (ev.key.code == Keyboard::Q) {
            changeTileSise(-1); audio.playSound(buttonS);
        }
        if (ev.key.code == Keyboard::E) {
            changeTileSise(1); audio.playSound(buttonS);
        }
        if (ev.key.code == Keyboard::S) {
            audio.playSound(buttonS); audio.OnOffSound();
        }
        if (ev.key.code == Keyboard::M) {
            if(isEnableDemonicLevel)
                audio.OnOffMusic(); audio.playSound(buttonS);
        }
        
    }
    if (ev.type == sf::Event::MouseButtonPressed)
    {
        if (ev.mouseButton.button == sf::Mouse::Left)
        {
            leftClick(ev.mouseButton.x, ev.mouseButton.y);
        }
        if (ev.mouseButton.button == sf::Mouse::Right)
        {
            rightClick(ev.mouseButton.x, ev.mouseButton.y);
        }
    }
    /*if (Keyboard::isKeyPressed(Keyboard::R)) {
        createWindow(500, 500);
    }*/
    
}
void WindowManager::createWindow(int wight, int height) {
    window.clear();
    if (wight < 1) {
        wight = 1;
    }
    if (height < 1) {
        height = 1;
    }
    window.create(VideoMode(wight, height), L"Bomb", Style::Default);
}
void WindowManager::leftClick(int x, int y) {
   
   
    //    rec.setSize(Vector2f(30, 30));
   // rec.setFillColor(Color(100, 100, 100));
    //rec.setPosition(width / 2 - 15, 12);
    if(sceneNum == 1){
        if (x >= width / 2 - 15 && x <= width / 2 + 15 && y >= 12 && y <= 42) {
            mainButtone();
            audio.playSound(buttonS);
        }
        else if (y - 2 * betweenTileSize - edgeSize > 0) {



            int c1 = (x - betweenTileSize) / (betweenTileSize + tileSize);
            int c2 = (y - 2 * betweenTileSize - edgeSize) / (betweenTileSize + tileSize);
            if (c1 >= 0 && c2 >= 0 && c1 < gameSizeX && c2 < gameSizeY) {

                if (!soundPlyed && game.leftClickProcessing(c1, c2)) {
                    audio.playSound(tileS);
                }
                if (game.getIsBad() && !soundPlyed) {
                    soundPlyed = true;

                    if (bombDensity == 100 && isEnableDemonicLevel)
                        audio.playSound(extraBoomS);
                    else
                        audio.playSound(boomS);
                }
                if (game.getIsSeccess() && !soundPlyed) {
                    audio.playSound(victoriS);
                    soundPlyed = true;
                }



            }

        }
    }
    


         //tileSize = 20;
    //betweenTileSize = 2;
    //edgeSize = 50;
    // (i + 1)* betweenTileSize + i * tileSize = x1   
    // (j + 2)* betweenTileSize + j * tileSize + edgeSize = x2     
    
    
}
void WindowManager::rightClick(int x, int y) {
    if (sceneNum == 1){
        int c1 = (x - betweenTileSize) / (betweenTileSize + tileSize);
        int c2 = (y - 2 * betweenTileSize - edgeSize) / (betweenTileSize + tileSize);
        if (c1 >= 0 && c2 >= 0 && c1 < gameSizeX && c2 < gameSizeY) {

            if (!soundPlyed && game.rightClickProcessing(c1, c2)) {
                audio.playSound(flagS);
            }
            if (game.getIsSeccess() && !soundPlyed) {
                audio.playSound(victoriS);
                soundPlyed = true;
            }

        }
    }
}
void WindowManager::mainButtone() {
    restartGame();
}
void WindowManager::enableDemonicLevel() {
    if(sceneNum !=1)
    {
        if (!isEnableDemonicLevel)
        {
            audio.playMusic();
            isEnableDemonicLevel = true;

            changeBombSum(0);
            changeSize(0);
        }
        else
        {
            if (audio.isMusicOn()) {
                audio.playMusic();
            }
            isEnableDemonicLevel = false;
            tileSize = 20;
            changeBombSum(0);
            changeSize(0);
        }
    }
}
void WindowManager::restartGame() {
    soundPlyed = false;
    game.restart();
}