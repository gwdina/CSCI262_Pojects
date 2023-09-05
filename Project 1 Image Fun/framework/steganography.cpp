//
// Created by gwdin on 2/3/2022.
//

#include <iostream>

#include "steganography.h"
#include "utility.h"

using namespace std;

bool steganography::execute(picture &p, const string &command) {
    if (command == "conceal") {
        string prompt = "Enter the text to conceal.  You can enter multiple lines; enter a blank line(space)\nto stop";
        string message = utility::get_lines(prompt); //STEGOHello World\0
        message = string("STEGO") + message;
        message.push_back('\0');
        _conceal(p, message);
    }
    else if (command == "reveal"){
        _reveal(p);
    }


    else {
        cout << "Unknown command: " << command << endl;
        return false;
    }

    return true;
}

bool steganography::_conceal(picture &p, string message){
   // message= "STEGOrun\0";
    int w = p.width();
    int h = p.height();
    int x = 0;
    int y = 0;

    int red;
    int green;
    int blue;
    // storing letter (8bit) in 8 bits of RGB (R0,G0,B0)(R1,G1,B1)(R2,G2)

    unsigned char letter;

    if ((message.size()+6) > (w*h)/3){
        cout << "image isn't large enough to store the message";
        return false;
    }

    else{
        for(int i=0; i < message.size(); ++i){
            letter = message[i];

            red = p.red(x,y);
            green = p.green(x,y);
            blue = p.blue(x,y);
            if ((letter >> 7) ==1){
                if((red%2) == 0){
                    red += 1;
                }
            }
            else{
                if((red%2) != 0){
                    red -= 1;
                }
            }

            if ((letter >> 6)%2 ==1){
                if((green%2) == 0){
                    green += 1;
                }
            }
            else{
                if((green%2) != 0){
                    green -= 1;
                }
            }

            if ((letter >> 5)%2==1){
                if((blue%2) == 0){
                    blue += 1;
                }
            }
            else{
                if((blue%2) != 0){
                    blue -= 1;
                }
            }

            p.set(x,y,red,green,blue);
            x += 1;
            if (x == w){
                x = 0;
                y += 1;
            }

            red = p.red(x,y);
            green = p.green(x,y);
            blue = p.blue(x,y);
            if ((letter >> 4)%2 ==1){
                if((red%2) == 0){
                    red += 1;
                }
            }
            else{
                if((red%2) != 0){
                    red -= 1;
                }
            }

            if ((letter >> 3)%2 ==1){
                if((green%2) == 0){
                    green += 1;
                }
            }
            else{
                if((green%2) != 0){
                    green -= 1;
                }
            }

            if ((letter >> 2)%2==1){
                if((blue%2) == 0){
                    blue += 1;
                }
            }
            else{
                if((blue%2) != 0){
                    blue -= 1;
                }
            }

            p.set(x,y,red,green,blue);
            x += 1;
            if (x == w){
                x = 0;
                y += 1;
            }

            red = p.red(x,y);
            green = p.green(x,y);
            blue = p.blue(x,y);
            if ((letter >> 1)%2 ==1){
                if((red%2) == 0){
                    red += 1;
                }
            }
            else{
                if((red%2) != 0){
                    red -= 1;
                }
            }

            if ((letter >> 0)%2 ==1){
                if((green%2) == 0){
                    green += 1;
                }
            }
            else{
                if((green%2) != 0){
                    green -= 1;
                }
            }

            p.set(x,y,red,green,blue);
            x += 1;
            if (x == w){
                x = 0;
                y += 1;
            }
        }
        cout << "message is safely concealed" << endl;
        return true;
    }


}

void steganography::_reveal(picture &p){
    int w = p.width();
    int x = 0;
    int y = 0;

    int red;
    int green;
    int blue;

    string hidden;
    unsigned char letter;

    while(true){
        letter = 0;

        red = p.red(x,y);
        green = p.green(x,y);
        blue = p.blue(x,y);

        if ((red)%2 ==1){
            letter += 1;
        }
        letter *= 2;
        if ((green)%2 ==1){
            letter += 1;
        }
        letter *= 2;
        if ((blue)%2 ==1){
            letter += 1;
        }
        letter *= 2;


        x += 1;
        if (x == w){
            x = 0;
            y += 1;
        }

        red = p.red(x,y);
        green = p.green(x,y);
        blue = p.blue(x,y);

        if ((red)%2 ==1){
            letter += 1;
        }
        letter *= 2;
        if ((green)%2 ==1){
            letter += 1;
        }
        letter *= 2;
        if ((blue)%2 ==1){
            letter += 1;
        }
        letter *= 2;


        x += 1;
        if (x == w){
            x = 0;
            y += 1;
        }

        red = p.red(x,y);
        green = p.green(x,y);


        if ((red)%2 ==1){
            letter += 1;
        }
        letter *= 2;
        if ((green)%2 ==1){
            letter += 1;
        }



        x += 1;
        if (x == w){
            x = 0;
            y += 1;
        }
        if(letter == '\0'){
            break;
        }

        hidden.push_back(letter);
    }


    if (hidden.substr(0,5) == "STEGO"){
        cout << hidden.substr(5) << endl;
    }

    else{
        cout << "No STEGO" << endl;
    }

}


