#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Product{
private:
    int starting_day;
    char product_name;
    int planed_q;
    char product_proces[5];
    int proces_to_do[5];
    int done_q {0};
    int time_in_production;
public:
    Product(char a ,int q, char *arr){
        product_name = a;
        planed_q = q;
        for(int i = 0; i<5; ++i){
            product_proces[i] = arr[i];
        }
        for(int i = 0; i<5; ++i){
            proces_to_do[i] = q;
        }
    }
    void set_product_name(char c){
        product_name = c;
    }
    char get_product_name(){
        return product_name;
    }
    void set_planed_q(int i){
        planed_q = i;
    }
    int get_planed_q(){
        return planed_q;
    }
    void set_done_q(int i){
        done_q = i;
    }
    int get_done_q(){
        return done_q;
    }
    int* get_proces_to_do(){
        int *arr = new int[5];
        arr = proces_to_do;
        return arr;
    }
    char* get_product_proces(){
        char *arr = new char[5];
        for(int i=0; i<5; ++i){
            arr[i] = product_proces[i];
        }
        return arr;
    }
    void set_proces_to_do(int *arr){
            for(int i = 0; i<5;++i){
                proces_to_do[i] = arr[i];
            }
        }
    void set_starting_day(int d){
        starting_day = d;
    }
    void set_time_in_production(int t){
        time_in_production = t;
    }
    int get_starting_time(){
        return starting_day;
    }
    string toString(){
        string s = "Product type: ";
        s.push_back(product_name);
        s += "\n";
        s += "Starting hour: " + to_string(starting_day) + "\n"; 
        s += "Finished quantity: " + to_string(done_q) +"\n";
        s += "Flow hours: " + to_string(time_in_production) + "\n\n";
        return s;
    }
    int get_time_in_production(){
        return time_in_production;
        }
};


int main() {
        /*
         * A - Natikanje krtack
         * B - Rocno varjenje
         * C - Vstavljanje vezja
         * D - Varjenje vezja
         * E - Rocno varjenje vezja
         * F - Zalivanje vezja
         * G - Meritev izdelka
         */
        //char operations[7] {'A','B','C','D','E','F','G'}; 
        //int product_per_hour[7] {500, 500, 500, 125, 500, 500, 125};
        char *product1_oper = new char[5]{'A', 'B', 'D','F', 'G'};
        char *product2_oper = new char[5]{'A','C','B','E','G'};
        Product p1A {'a',2000, product1_oper}; //2×
        Product p1B {'a',1000,product1_oper};//4×
        Product p1C {'a',500,product1_oper};//4×
        Product p2A {'b',1000,product2_oper};//2×
        int stock_on_operation [7] {0};
        vector<Product> in_production;
        vector<Product> finished_products;
        vector<Product> p_proces[7];
        int fp_size = finished_products.size();
        vector<Product> products {p1C, p1C, p1B, p1A, p1B, p2A,p1C, p1C, p1B, p1A, p1B, p2A,
        p1C, p1C, p1B, p1A, p1B, p2A,p1C, p1C, p1B, p1A, p1B, p2A,
        p1C, p1C, p1B, p1A, p1B, p2A,p1C, p1C, p1B, p1A, p1B, p2A,
        p1C, p1C, p1B, p1A, p1B, p2A,p1C, p1C, p1B, p1A, p1B, p2A,
        p1C, p1C, p1B, p1A, p1B, p2A,p1C, p1C, p1B, p1A, p1B, p2A,
        p1C, p1C, p1B, p1A, p1B, p2A,p1C, p1C, p1B, p1A, p1B, p2A,
        p1C, p1C, p1B, p1A, p1B, p2A,p1C, p1C, p1B, p1A, p1B, p2A,
        p1C, p1C, p1B, p1A, p1B, p2A,p1C, p1C, p1B, p1A, p1B, p2A,
        p1C, p1C, p1B, p1A, p1B, p2A,p1C, p1C, p1B, p1A, p1B, p2A,
        p1C, p1C, p1B, p1A, p1B, p2A,p1C, p1C, p1B, p1A, p1B, p2A,
        p1C, p1C, p1B, p1A, p1B, p2A,p1C, p1C, p1B, p1A, p1B, p2A,
        p1C, p1C, p1B, p1A, p1B, p2A,p1C, p1C, p1B, p1A, p1B, p2A};
        int hour {0};
        //int hour_p {8};
        int overtime{0};
        bool izmena {true};
        int days {0};
        int working_hour{0};
        ofstream file;
        //char fw;
        int b1 ;
        int b2 ;
		cout << "Type number of the first buffer: ";
		cin >> b1;
		cout << "Type number for the second buffer: ";
		cin >> b2;
        string txt_name = "ClanekBufferOT_"+to_string(b1)+"_"+to_string(b2)+".txt";
        file.open(txt_name);
        file << "Buffer za D = " << b1 << " in buffer za G = "<< b2 <<" .\n\n";
        do{
            hour++;
            if(!izmena){
                overtime++;
            }else{
                working_hour++;
            }
            if((hour-1)%8 == 0 && (hour-1)!=0){
                if(izmena){
                    izmena = false;
                   // file << "Zacetek druge izmene\n\n";
                }else{
                    izmena = true;
                   // file << "Zacetek prve izmene\n\n";
                }
            }
            if(hour%16 == 0){
                days++;
            }
            //file << "Starting hour " << hour << "\n\n";
            
            int oA_size = p_proces[0].size();
            int oB_size = p_proces[1].size();
            int oC_size = p_proces[2].size();
            int oD_size = p_proces[3].size();
            int oE_size = p_proces[4].size();
            int oF_size = p_proces[5].size();
            int oG_size = p_proces[6].size();
            int p_size = products.size();
            int buffer1{0};
            int buffer2{0};
            for(int i = 0; i<oD_size;i++){
                int *arr = new int[5];
                arr = p_proces[3].at(i).get_proces_to_do();
                buffer1 += arr[3];
            }
            for(int i = 0; i<oG_size;i++){
                int *arr = new int[5];
                arr = p_proces[6].at(i).get_proces_to_do();
                buffer2 += arr[6];
            }
            if(p_size > 0 && izmena && buffer1 < b1 && buffer2 < b2){
                
                products.at(0).set_starting_day(working_hour);
                in_production.push_back(products.at(0));
                products.erase(products.begin());
            }
            int ip_size = in_production.size();
            
            while(ip_size > 0 && izmena){
                
                int *arr = new int[5];
                arr = in_production.at(0).get_proces_to_do();
                char *arr_p = new char[5];
                arr_p = in_production.at(0).get_product_proces();
                
                for(int i = 0; i < 5; i++){
                    if(arr[i] > 0 && arr_p[i] == 'A'){
                       
                        p_proces[0].push_back(in_production.at(0));
                        in_production.erase(in_production.begin());
                        break;
                    }else if(arr[i] > 0 && arr_p[i] == 'B'){
                        p_proces[1].push_back(in_production.at(0));
                        in_production.erase(in_production.begin());
                        break;
                    }else if(arr[i] > 0 && arr_p[i] == 'C'){
                        p_proces[2].push_back(in_production.at(0));
                        in_production.erase(in_production.begin());
                        break;
                    }else if(arr[i] > 0 && arr_p[i] == 'D'){
                        p_proces[3].push_back(in_production.at(0));
                        in_production.erase(in_production.begin());
                        break;
                    }else if(arr[i] > 0 && arr_p[i] == 'E'){
                        p_proces[4].push_back(in_production.at(0));
                        in_production.erase(in_production.begin());
                        break;
                    }else if(arr[i] > 0 && arr_p[i] == 'F'){
                        p_proces[5].push_back(in_production.at(0));
                        in_production.erase(in_production.begin());
                        break;
                    }else if(arr[i] > 0 && arr_p[i] == 'G'){
                        p_proces[6].push_back(in_production.at(0));
                        in_production.erase(in_production.begin());
                        break;
                    }
                    
                }
                ip_size = in_production.size();
                
            }
            oA_size = p_proces[0].size();
            oB_size = p_proces[1].size();
            oC_size = p_proces[2].size();
            oD_size = p_proces[3].size();
            oE_size = p_proces[4].size();
            oF_size = p_proces[5].size();
            oG_size = p_proces[6].size();
            
            if(oA_size > 0 && izmena){
                
                int *arr = new int[5];
                arr = p_proces[0].at(0).get_proces_to_do();
                char *arr_p = new char[5];
                arr_p = p_proces[0].at(0).get_product_proces();
                for(int i=0;i<5;++i){
                    if(arr[i] > 0 && arr_p[i] == 'A'){
                        if(arr[i] <= 500){
                            stock_on_operation[0] += arr[i];
                            arr[i] = 0;
                            p_proces[0].at(0).set_proces_to_do(arr);
                            in_production.push_back(p_proces[0].at(0));
                            p_proces[0].erase(p_proces[0].begin());
                        }else{
                            arr[i] -= 500;
                            stock_on_operation[0] += 500;
                            p_proces[0].at(0).set_proces_to_do(arr);
                        }
                    }
                }
            }
            if(oB_size > 0 && izmena){
                
                int *arr = new int[5];
                arr = p_proces[1].at(0).get_proces_to_do();
                char *arr_p = new char[5];
                arr_p = p_proces[1].at(0).get_product_proces();
                char p_name = p_proces[1].at(0).get_product_name();
                for(int i=0;i<5;++i){
                    if(arr[i] > 0 && arr_p[i] == 'B'){
                        if(arr[i] <= 500){
                            if(p_name == 'a'){
                                 stock_on_operation[0] -= arr[i];
                                stock_on_operation[1] += arr[i];
                            }else{
                                stock_on_operation[2] -= arr[i];
                                stock_on_operation[1] += arr[i];
                            }
                            arr[i] = 0;
                            p_proces[1].at(0).set_proces_to_do(arr);
                            in_production.push_back(p_proces[1].at(0));
                            p_proces[1].erase(p_proces[1].begin());
                        }else{
                            arr[i] -= 500;
                            if(p_name == 'a'){
                                 stock_on_operation[0] -= 500;
                                stock_on_operation[1] += 500;
                            }else{
                                stock_on_operation[2] -= 500;
                                stock_on_operation[1] += 500;
                            }
                            p_proces[1].at(0).set_proces_to_do(arr);
                        }
                    }
                }
            }
            
            if(oC_size > 0 && izmena){
                
                int *arr = new int[5];
                arr = p_proces[2].at(0).get_proces_to_do();
                char *arr_p = new char[5];
                arr_p = p_proces[2].at(0).get_product_proces();
                for(int i=0;i<5;++i){
                    if(arr[i] > 0 && arr_p[i] == 'C'){
                        if(arr[i] <= 500){
                            stock_on_operation[0] -= arr[i];
                            stock_on_operation[2] += arr[i];
                            arr[i] = 0;
                            p_proces[2].at(0).set_proces_to_do(arr);
                            in_production.push_back(p_proces[2].at(0));
                            p_proces[2].erase(p_proces[2].begin());
                            break;
                        }else{
                            arr[i] -= 500;
                            stock_on_operation[0] -= 500;
                            stock_on_operation[2] += 500;
                            p_proces[2].at(0).set_proces_to_do(arr);
                            break;
                        }
                    }
                }
            }
            if(oD_size > 0){
               
                int *arr = new int[5];
                arr = p_proces[3].at(0).get_proces_to_do();
                char *arr_p = new char[5];
                arr_p = p_proces[3].at(0).get_product_proces();
                for(int i=0;i<5;++i){
                    if(arr[i] > 0 && arr_p[i] == 'D'){
                        if(arr[i] <= 125){
                            stock_on_operation[1] -= arr[i];
                            stock_on_operation[3] += arr[i];
                            arr[i] = 0;
                            p_proces[3].at(0).set_proces_to_do(arr);
                            in_production.push_back(p_proces[3].at(0));
                            p_proces[3].erase(p_proces[3].begin());
                        }else{
                            arr[i] -= 125;
                            stock_on_operation[1] -= 125;
                            stock_on_operation[3] += 125;
                            p_proces[3].at(0).set_proces_to_do(arr);
                        }
                    }
                }
            }
            if(oE_size > 0 && izmena){
              
                int *arr = new int[5];
                arr = p_proces[4].at(0).get_proces_to_do();
                char *arr_p = new char[5];
                arr_p = p_proces[4].at(0).get_product_proces();
                for(int i=0;i<5;++i){
                    if(arr[i] > 0 && arr_p[i] == 'E'){
                        if(arr[i] <= 500){
                            stock_on_operation[1] -= arr[i];
                            stock_on_operation[4] += arr[i];
                            arr[i] = 0;
                            p_proces[4].at(0).set_proces_to_do(arr);
                            in_production.push_back(p_proces[4].at(0));
                            p_proces[4].erase(p_proces[4].begin());
                        }else{
                            arr[i] -= 500;
                            stock_on_operation[1] -= 500;
                            stock_on_operation[4] += 500;
                            p_proces[4].at(0).set_proces_to_do(arr);
                        }
                    }
                }
            }
            if(oF_size > 0 && izmena){
                
                int *arr = new int[5];
                arr = p_proces[5].at(0).get_proces_to_do();
                char *arr_p = new char[5];
                arr_p = p_proces[5].at(0).get_product_proces();
                for(int i=0;i<5;++i){
                    if(arr[i] > 0 && arr_p[i] == 'F'){
                        if(arr[i] <= 500){
                            stock_on_operation[3] -= arr[i];
                            stock_on_operation[5] += arr[i];
                            arr[i] = 0;
                            p_proces[5].at(0).set_proces_to_do(arr);
                            in_production.push_back(p_proces[5].at(0));
                            p_proces[5].erase(p_proces[5].begin());
                        }else{
                            arr[i] -= 500;
                            stock_on_operation[3] -= 500;
                            stock_on_operation[5] += 500;
                            p_proces[5].at(0).set_proces_to_do(arr);
                        }
                    }
                }
            }
            if(oG_size > 0){
                
                int *arr = new int[5];
                arr = p_proces[6].at(0).get_proces_to_do();
                char *arr_p = new char[5];
                arr_p = p_proces[6].at(0).get_product_proces();
                
                    if(arr[4] > 0 && arr_p[4] == 'G'){
                        
                        if(arr[4] <= 250 && p_proces[6].at(0).get_product_name() == 'b'){
                            stock_on_operation[4] -= arr[4];
                            stock_on_operation[6] += arr[4];
                            arr[4] = 0;
                            p_proces[6].at(0).set_done_q(p_proces[6].at(0).get_done_q()+250);
                            p_proces[6].at(0).set_proces_to_do(arr);
                            p_proces[6].at(0).set_time_in_production(hour-p_proces[6].at(0).get_starting_time());
                            finished_products.push_back(p_proces[6].at(0));
                            p_proces[6].erase(p_proces[6].begin());
                        }else if(arr[4] <= 125 && p_proces[6].at(0).get_product_name() == 'a'){
                            stock_on_operation[5] -= arr[4];
                            stock_on_operation[6] += arr[4];
                            p_proces[6].at(0).set_done_q(p_proces[6].at(0).get_done_q()+125);
                            arr[4] = 0;
                            p_proces[6].at(0).set_proces_to_do(arr);
                            p_proces[6].at(0).set_time_in_production(hour-p_proces[6].at(0).get_starting_time());
                            finished_products.push_back(p_proces[6].at(0));
                            p_proces[6].erase(p_proces[6].begin());
                        }
                        else{
                            
                            if(p_proces[6].at(0).get_product_name() == 'a'){
                                arr[4] -= 125;
                                stock_on_operation[5] -= 125;
                                stock_on_operation[6] += 125;
                                p_proces[6].at(0).set_done_q(p_proces[6].at(0).get_done_q()+125);
                            }else{
                                arr[4] -= 250;
                                stock_on_operation[4] -= 250;
                                stock_on_operation[6] += 250;
                                p_proces[6].at(0).set_done_q(p_proces[6].at(0).get_done_q()+250);
                            }
                            p_proces[6].at(0).set_proces_to_do(arr);
                            
                        }
                    }
            }
            /*file << "Stock on operations from A-G\n";
            for(int i = 0; i<7;++i){
                file << stock_on_operation[i] <<" ";
            }
            file <<"\n\n";*/
            fp_size = finished_products.size();
        }while(fp_size < 144);
        /*for(int i = 0; i < 144 ; ++i){
            file << finished_products.at(i).toString();
        }*/
        
        for(int m = 0; m<12; ++m){
            for(int i = 0+m*12; i < 12*(m+1) ; ++i){
                
                        if(finished_products.at(i).get_starting_time() > 99){
                            file << "| " << finished_products.at(i).get_starting_time() << " ";
                            
                        }else if(finished_products.at(i).get_starting_time() > 9){
                            file << "|  " << finished_products.at(i).get_starting_time() << " ";
                            
                        }else{
                            file << "|   " << finished_products.at(i).get_starting_time() << " ";
                            
                        }
            }
            file << "|\n";
            for(int i = 0+m*12; i < 12*(m+1) ; ++i){
                        if(finished_products.at(i).get_time_in_production() > 99){
                            file << "| " << finished_products.at(i).get_time_in_production() << " ";
                        }else if(finished_products.at(i).get_time_in_production() > 9){
                            file << "|  " << finished_products.at(i).get_time_in_production() << " ";
                        }else{
                            file << "|   " << finished_products.at(i).get_time_in_production() << " ";
                        }
            }
            file << "|\n\n";
        }
        file << "|\n\n";
        file << "Porabljenih je bilo " << hour << " ur, od tega\n";
        file << hour-overtime << " ur v prvi izmeni in\n";
        file << overtime << " ur v drugi izmeni\n";
        file << "To pomeni " << days << " dni\n";
        file.close();
         ofstream file_csv;
        file_csv.open("ClanekCSV.txt");
            for(int i = 0; i < 144 ; ++i){ 
                        if(i == 143){
                            file_csv << finished_products.at(i).get_starting_time() ;
                        }else{
                            file_csv << finished_products.at(i).get_starting_time()<< ",";
                            
                        }
            }
            file_csv << "|\n";
            for(int i = 0; i < 144 ; ++i){
                        if(i == 143){
                            file_csv << finished_products.at(i).get_time_in_production() ;
                        }else{
                            file_csv << finished_products.at(i).get_time_in_production()<< ",";
                        }
            }
        file_csv.close();
        return 0;
}