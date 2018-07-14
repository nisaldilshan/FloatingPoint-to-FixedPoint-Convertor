#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

uint64_t frac_mask = 0x000fffffffffffff;
uint64_t additional_one = 0x0010000000000000;
uint64_t power_mask = 0x7ff0000000000000;
uint64_t sign_bit = 0x8000000000000000;

union udouble{
    double d;
    uint64_t u;
}numd;

uint64_t double_to_fix_point(double fnum,int int_bits,int float_bits){//
	if(fnum == 0.0 ) return 0;
	numd.d = fnum;

    uint64_t frac = additional_one + (frac_mask & numd.u);
    int expo = ((power_mask & numd.u)>>52)-1023;
    uint64_t converted = frac>>(52-float_bits-expo);//float 8,8 fix point

    if(numd.u & sign_bit){
        uint64_t mask = 0x0000000000000001;
        for(int i=1;i<(int_bits+float_bits);i++){
            mask<<=1;
            mask= mask + (uint64_t)1;
        }
        converted=converted^mask;//mask;
        converted=converted + (uint64_t)1;
    }
    return converted;
	//return numd.u;
}

uint64_t numb;

int main()
{
    double x;
    int cou = 0;
    int select = 0;
    string line;
    ifstream myfilein ("input.txt");
    ofstream myfileout;
    myfileout.open ("output.txt");
    if (myfilein.is_open())
      {
        while (true)
        {
            if(cou==64){
                cou=0;
                break;
            }
            myfilein >> x;
            myfileout << std::setw(2) << std::setfill('0')<< "A_inverse[" << std::dec << cou << "] = "<< std::hex <<  "40'h" << double_to_fix_point(x,16,24) <<  ";\n";
            cou++;
            //cout << cou << endl;
        }
        while(true){
            //getline (myfilein,line);
            //cout << line << '\n';
            myfilein >> x;
            if(x ==54.54){
                cou = 0;
                select = 1;
                continue;
            }
            else if(x ==45.45){
                cou = 0;
                select = 2;
                continue;
            }
            else if(x ==23.23){
                cou = 0;
                select = 3;
                continue;
            }
            else if(x ==32.32){
                cou = 0;
                select = 4;
                continue;
            }
            else if(x ==65.65){
                cou = 0;
                select = 5;
                continue;
            }
            else if(x ==56.56){
                cou = 0;
                select = 6;
                continue;
            }
            else if(x ==11.11){
                cou=0;
                select =0;
                break;
            }


            if(select == 1){
                myfileout << std::setw(2) << std::setfill('0')<< "V_SOURCE[" << std::dec << cou << "] = "<< std::hex <<  "40'h" << double_to_fix_point(x,16,24) <<  ";\n";
                cou++;
            }
            else if(select == 2){
                myfileout << std::setw(2) << std::setfill('0')<< "SWITCHES[" << std::dec << cou << "] = "<< std::hex <<  "24'h" << double_to_fix_point(x,16,24) <<  ";\n";
                cou++;
            }
            else if(select == 3){
                myfileout << std::setw(2) << std::setfill('0')<< "Node_1[" << std::dec << cou << "] = "<< std::dec <<  "4'd" << x <<  ";\n";
                cou++;
            }
            else if(select == 4){
                myfileout << std::setw(2) << std::setfill('0')<< "Node_2[" << std::dec << cou << "] = "<< std::dec <<  "4'd" << x <<  ";\n";
                cou++;
            }
            else if(select == 5){
                myfileout << std::setw(2) << std::setfill('0')<< "G_table[" << std::dec << cou << "] = "<< std::hex <<  "40'h" << double_to_fix_point(x,16,24) <<  ";\n";
                cou++;
            }
            else if(select == 6){
                myfileout << std::setw(2) << std::setfill('0')<< "G_state[" << std::dec << cou << "] = "<< std::dec <<  "1'd" << x <<  ";\n";
                cou++;
            }
            else{
                if(cou==0){
                    myfileout << std::setw(2) << std::setfill('0')<< "numNode" << " = "<< std::dec <<  "3'd" << x <<  ";\n";
                }
                if(cou==1){
                    myfileout << std::setw(2) << std::setfill('0')<< "numVolSource" << " = "<< std::dec <<  "3'd" << x <<  ";\n";
                }
                if(cou==2){
                    myfileout << std::setw(2) << std::setfill('0')<< "L_count" << " = "<< std::dec <<  "3'd" << x <<  ";\n";
                }
                if(cou==3){
                    myfileout << std::setw(2) << std::setfill('0')<< "C_count" << " = "<< std::dec <<  "3'd" << x <<  ";\n";
                }
                if(cou==4){
                    myfileout << std::setw(2) << std::setfill('0')<< "SW_count" << " = "<< std::dec <<  "3'd" << x <<  ";\n";
                }
                if(cou==5){
                    myfileout << std::setw(2) << std::setfill('0')<< "D_count" << " = " << std::dec <<  "3'd" << x <<  ";\n";
                }
                if(cou==6){
                    myfileout << std::setw(2) << std::setfill('0')<< "J_src_count" << " = "<< std::dec <<  "5'd" << x <<  ";\n";
                }
                cou++;
            }
        }

        myfilein.close();
        myfileout.close();
      }

    return 0;
}
