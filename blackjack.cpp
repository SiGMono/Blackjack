#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

void Ponownie();

void Blackjack(){
    vector<int> pull = {1,2,3,4,5,6,7,8,9,10,11,12,13,1,2,3,4,5,6,7,8,9,10,11,12,13,1,2,3,4,5,6,7,8,9,10,11,12,13,1,2,3,4,5,6,7,8,9,10,11,12,13};       //pula wszystkich kart
    vector<int> player = {};    //inicjalizowana pula gracza
    vector<int> dealer = {};    //inicjalizowana pula dilera

    random_device rd;           //losowy numer
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0,pull.size()-1);     //od 0 do maksimum vectora dla indeksow puli

    cout<<"Czy dealer ma uderzac miekkie 17-tki? (T/N)"<<endl;
    string soft_check = "";
    while(soft_check != "T" && soft_check != "N"){
        cin>>soft_check;
    }

    string x = "V";                     //Zmienna kontynuacji udzerzen przez gracza

    bool player_bust = false;
    bool dealer_bust = false;

    int player_val = 0;
    int dealer_val = 0;

    int hidden_card = 1;

    while(true){
        int temp = distr(gen);
        while(pull.at(temp) == 0){      //jesli wartosc to zero to karta zostala juz uzyta i trzeba losowac znowu
            temp = distr(gen);
        }

        if(dealer.size() < 2 || player.size() < 2){         //przydielanie pierwszych dwoch kart
                if(player.size() > dealer.size()){
                    dealer.push_back(pull.at(temp));
                }else{
                    player.push_back(pull.at(temp));
                }
                pull.at(temp) = 0;
                sort(dealer.begin(),dealer.end(),greater<int>());
                sort(player.begin(),player.end(),greater<int>());
        }else{
            cout<<endl;
            cout<<"Karty dealera: "<<endl;                  //Wyswietlenie kart
            if(dealer_bust == true || player_bust == true){
                for(int i = 0; i < dealer.size(); i++){
                    switch(dealer.at(i)){
                    case 1:
                        cout<<"As";
                        break;
                    case 11:
                        cout<<"Jopek";
                        break;
                    case 12:
                        cout<<"Dama";
                        break;
                    case 13:
                        cout<<"Krol";
                        break;
                    default:
                        cout<<dealer.at(i);
                    }
                cout<<", ";
            }
            }else{
                for(int i = 0; i < dealer.size(); i++){
                if(i == hidden_card){
                    cout<<"#";
                }else{
                    switch(dealer.at(i)){
                    case 1:
                        cout<<"As";
                        break;
                    case 11:
                        cout<<"Jopek";
                        break;
                    case 12:
                        cout<<"Dama";
                        break;
                    case 13:
                        cout<<"Krol";
                        break;
                    default:
                        cout<<dealer.at(i);
                    }
                }
                cout<<", ";
            }
            }

            cout<<endl;
            cout<<"Karty gracza: "<<endl;
            for(int i = 0; i < player.size(); i++){
                switch(player.at(i)){
                    case 1:
                        cout<<"As";
                        break;
                    case 11:
                        cout<<"Jopek";
                        break;
                    case 12:
                        cout<<"Dama";
                        break;
                    case 13:
                        cout<<"Krol";
                        break;
                    default:
                        cout<<player.at(i);
                    }
                    cout<<", ";
            }

            cout<<endl;

            if(dealer_bust == true){
                cout<<"Dealer przebil 21. Wygrales!";cout<<endl;
                Ponownie();
            }

            if(player_bust == true){
                cout<<"Przebiles 21. Przegrales!";cout<<endl;
                Ponownie();
            }

            cout<<endl;

            cout<<"Uderzasz czy stoisz? (U/S): ";     //Dobieranie kart

            while(x != "U" && x != "S"){
                cin>>x;
            }

            if(x == "S" && dealer_val > 17){
                if(player_val > dealer_val){
                    cout<<"Wygrales!";cout<<endl;
                    Ponownie();
                }
                if(dealer_val > player_val){
                    cout<<"Przegrales";cout<<endl;
                    Ponownie();
                }
                if(dealer_val == player_val){
                    cout<<"Rowno";cout<<endl;
                    Ponownie();
                }
            }

            if(x == "U" || x == "S"){                                       //Logika uderzen grzacza
                if(x == "U"){
                    while(pull.at(temp) == 0){
                    temp = distr(gen);
                    }
                    player.push_back(pull.at(temp));
                    pull.at(temp) = 0;
                    sort(player.begin(), player.end(), greater<int>());         //Sortowanie aby ulatwic sprawdzanie asow
                }

                int player_val_temp = 0;                                    //Logika pelnej wartosci kart (z asami) i flaga przegranej dla gracza
                for(int i = 0; i < player.size(); i++){
                    if(player.at(i) == 1){
                        if(player.size() == i+1 && player_val_temp <= 10){
                            player_val_temp += 11;
                        }else{
                            player_val_temp++;
                        }
                    }else{
                        player_val_temp += player.at(i);
                    }
                }
                if(player_val_temp > 21){
                    player_bust = true;
                }
                x = "V";
                player_val = player_val_temp;
            }

            bool soft_ace = false;

            int dealer_val_temp = 0;                                //Logika pelnej wartosci kart (z asami) i flaga przegranej dla dealera
            for(int i = 0; i < dealer.size(); i++){
                if(dealer.at(i) == 1){
                    if(dealer.size() == i+1 && dealer_val_temp <= 10){
                        dealer_val_temp += 11;
                        soft_ace = true;
                    }else{
                        dealer_val_temp++;
                        soft_ace = false;
                    }
                }else{
                    dealer_val_temp += dealer.at(i);
                }
            }
            if(dealer_val_temp > 21){
                dealer_bust = true;
            }
            if(!dealer_bust && dealer_val_temp < 17){               //Logika uderzen dealera
                while(pull.at(temp) == 0){
                    temp = distr(gen);
                }
                if(dealer.at(hidden_card) < pull.at(temp)){
                    hidden_card++;
                }
                dealer.push_back(pull.at(temp));
                pull.at(temp) = 0;
            }
            if(!dealer_bust && dealer_val_temp == 17 && soft_check == "T" && soft_ace == true){     //logika twardych i miekkich 17-tek
                while(pull.at(temp) == 0){
                    temp = distr(gen);
                }
                if(dealer.at(hidden_card) < pull.at(temp)){
                    hidden_card++;
                }
                dealer.push_back(pull.at(temp));
                pull.at(temp) = 0;
            }
            dealer_val = dealer_val_temp;
            sort(dealer.begin(), dealer.end(), greater<int>());     //Sortowanie aby ulatwoc sprawdzanie asow
        }
    }
}

void Ponownie(){
    string cont = "";
    while(cont != "T" || cont != "N"){
        cout<<"Ponownie? (T/N):";
        cin>>cont;
    }
    if(cont == "T"){
        Blackjack();
    }
    if(cont == "N"){
        return;
    }
}

int main()
{
    Blackjack();
    Ponownie();
    return 0;
}
