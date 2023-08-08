#ifndef Gate_h
#define Gate_h
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Gate{
    public:
    Gate(){ }
    //==============================//
    //It returns type of class
    virtual string get_type()=0; 
    //==============================//
    //It returns the input names inside the class
    virtual string get_name_1()=0;
    virtual string get_name_2()=0;
    //==============================//
    //It returns the input values inside the class
    virtual int get_value_1()=0;
    virtual int get_value_2()=0;
    //==============================//
    //It returns the output names inside the class
    virtual string get_output_name() = 0;
    //==============================//
    //Functions that return custom output names for the decoder
    virtual string get_output_name_2() = 0;
    virtual string get_output_name_3() = 0;
    virtual string get_output_name_4() = 0;
    //==============================//
    //To set the input values ​​inside the class
    virtual void set_value_1(int x)=0;
    virtual void set_value_2(int x)=0;
    //==============================//
    //Performs calculations according to the given truth table
    virtual int evaluation() = 0;
    //==============================//
    //To set the output values ​​inside the class
    virtual void set_output_value(int x)= 0;
    //==============================//
    //Functions that set custom output values ​​for the decoder
    virtual void set_output_value_2(int x) = 0;
    virtual void set_output_value_3(int x) = 0;
    virtual void set_output_value_4(int x) = 0;
    //=============================//
    //Special set and get function for the former out value in the former out class
    virtual void set_former_out(int x) = 0;
    virtual int get_former_out_value() = 0;
    //=============================//
    //Function that returns the output value inside the class
    virtual int get_output_value() = 0;
    //Functions to return output values ​​inside the decoder class
    virtual int get_output_value_2() = 0;
    virtual int get_output_value_3()= 0;
    virtual int get_output_value_4() = 0;
};
class Input : public Gate{
    public:
        string type;//Holds class type
        string data_name;//Holds input name 
        int data_value;//Holds input value 


        Input(string name,int value){
            //Default settings
            data_name = name;
            type = "Input";
            data_value = value;
        }
        string get_type(){ return type;}//Returns class type;
        string get_name_1(){return data_name;}//Returns input name
        string get_name_2(){return "";}//Empty because of this function is for other classes

        int get_value_1(){ return data_value;}//Returns input value
        int get_value_2(){return -99;}//Empty because of this function is for other classes
        
        
        void set_value_1(int x){ data_value = x;}//sets the input value
        void set_value_2(int x){}//Empty because of this function is for other classes
        
        string get_output_name(){return "";}//Empty because of this function is for other classes

        
        //==============================//
        //all functions below are empty  because of these functions are for other classes//
        int get_output_value() {return -99; }
        void set_output_value(int x){ }

        void set_former_out(int x) { }
        string get_output_name_2(){return "";}
        string get_output_name_3(){return "";}
        string get_output_name_4(){return "";}

        void set_output_value_2(int x){ }
        void set_output_value_3(int x){ }
        void set_output_value_4(int x){ }

        int get_output_value_2() {return -99; }
        int get_output_value_3() { return -99;}
        int get_output_value_4() {return -99; }

        int get_former_out_value(){ return -30;}

        int evaluation(){return -1; }
};
class Output : public Gate{
    public:
        string type;//Holds class type
        string data_name;//Holds input name
        int data_value;//Holds input value
        
        Output(string name)//Default settings
        {
            type = "Output";
            data_name = name;
            data_value = -1;
        }
       
        
        
        string get_type(){ return type;}//Returns class type
        
                
        string get_name_1(){return data_name;}//Returns input name
        string get_name_2(){return "";}//Empty because of this function for other classes
        
        int get_value_1(){ return data_value;}//Returns input value
        int get_value_2(){return -99;}//Empty because of this function for other classes
        
        void set_value_1(int x){ data_value = x;}//Sets input value
        void set_value_2(int x){ }//Empty because of this function for other classes

        
        //==============================//
       //all functions below are empty  because of these functions are for other classes//
        


        string get_output_name(){return "";}
        string get_output_name_2(){return "";}
        string get_output_name_3(){return "";}
        string get_output_name_4(){return "";}

        void set_output_value(int x){ }
        void set_output_value_2(int x){ }
        void set_output_value_3(int x){ }
        void set_output_value_4(int x){ }

        
        int get_output_value() {return -99; }
        int get_output_value_2() { return -99;}
        int get_output_value_3() { return -99;}
        int get_output_value_4() { return -99;}

        int evaluation(){ return -1;}

        int get_former_out_value(){ return -30;}
        void set_former_out(int x) { }
          
};

class And : public Gate{
    public:
        string type;//Holds class type
        string input1;//Holds first input name
        string input2;//Holds second input name
        string output;//Holds output name
        
        int data_input1;//Holds first input value
        int data_input2;//Holds second input value
        int data_output;//Holds output value
        And(string in1,string in2,string out)//default settings
        {
            input1=in1;
            input2=in2;
            output = out;
            type = "And";
            data_input1 = -1;
            data_input2 = -1;
            data_output = -1;
        }
        
        string get_type(){ return type;}//Returns class type

        string get_name_1(){return input1;}//Returns first input name
        string get_name_2(){return input2;}//Returns second input name
        
        int get_value_1(){ return data_input1;}//Returns first input value
        int get_value_2(){return data_input2;}//Returns second input value

        void set_value_1(int x){ data_input1 = x;}//Sets first input value
        void set_value_2(int x){ data_input2 = x;}//Sets second input value

        string get_output_name(){return output;}//Return output name

        int get_output_value() {return data_output; }//Returns output value
        void set_output_value(int x){ data_output = x;}//Sets output value

        int evaluation()//Performs calculations according to the given truth table and return output value
        { 
            int result=33;
            if(data_input1 == 0 || data_input2 == 0)
            {
                result = 0;
            }
            else
            {
                result = 1;
            }
            data_output = result;
            return result;

        }
           
        //==============================//
        //all functions below are empty  because of these functions are for other classes//
        
        string get_output_name_2(){return "";}
        string get_output_name_3(){return "";}
        string get_output_name_4(){return "";}
        
        void set_output_value_2(int x){ }
        void set_output_value_3(int x){ }
        void set_output_value_4(int x){ }

        int get_output_value_2() { return -99;}
        int get_output_value_3() {return -99; }
        int get_output_value_4() { return -99;}

        int get_former_out_value(){ return -30;}
        void set_former_out(int x) { }

};
class Or : public Gate{
    public:
        string input1;//Holds input1 name
        string input2;//Holds input2 name
        string output;//Holds output name

        int data_input1;//Holds input1 value
        int data_input2;//Holds input2 value
        int data_output;//Holds output value

        string type;//Holds class type

        Or(string in1,string in2,string out)//Default settings
        {
            input1=in1;
            input2=in2;
            output = out;
            type = "Or";
            data_input1 = -1;
            data_input2 = -1;
            data_output = -1;
        }
        //Performs calculations according to the given truth table and return output value
        int evaluation(){
            int result=33;
            if(data_input1 == 1 || data_input2 == 1)
            {
                result = 1;
            }
            else
            {
                result = 0;
            }
            data_output = result;
            return result;

         }
        string get_type(){ return type;}//Returns class type

        string get_name_1(){return input1;}//returns input1 name
        string get_name_2(){return input2;}//Returns input2 name

        int get_value_1(){ return data_input1;}//returns input1 value
        int get_value_2(){return data_input2;}//returns input2 value

        void set_value_1(int x){ data_input1 = x;}//Sets input1 value
        void set_value_2(int x){ data_input2 = x;}//Sets input2 value
        
        string get_output_name(){return output;}//Returns output name
        int get_output_value() {return data_output; }//Returns output value
        void set_output_value(int x){ data_output = x;}//sets output value
        
        //==============================//
        //all functions below are empty  because of these functions are for other classes//
        string get_output_name_2(){return "";}
        string get_output_name_3(){return "";}
        string get_output_name_4(){return "";}

        void set_output_value_2(int x){ }
        void set_output_value_3(int x){ }
        void set_output_value_4(int x){ }

        int get_output_value_2() { return -99;}
        int get_output_value_3() {return -99; }
        int get_output_value_4() { return -99;}

        int get_former_out_value(){ return -30;}
        void set_former_out(int x) { }
        
};
class Not : public Gate{
    public:
    
        string type;//holds type
        string input;//holds input name
        string output;//holds output name

        int data_input;//holds input value
        int data_output;//holds output value

        Not(string in,string out){
            input = in;
            output = out;
            type = "Not";
            data_input = -1;
            data_output = -1;
        }
        //Performs calculations according to the given truth table and return output value
        int evaluation(){
            int result;
            if(data_input == 0)
            {
                result = 1;
            }
            else if(data_input == 1)
            {
                result = 0;
            }
            data_output = result;
            return result;
         }
        string get_type(){ return type;}  //returns class type
        string get_name_1(){return input;}//returns input name


        string get_output_name(){return output;}//returns output name
        
        int get_value_1(){ return data_input;}//returns input value
        void set_value_1(int x){data_input = x;}//sets input value

        int get_output_value() {return data_output; }//returns output value
        void set_output_value(int x){ data_output = x;}//sets output value

        //==============================//
        //all functions below are empty  because of these functions are for other classes//

        void set_value_2(int x){ };
        int get_value_2(){return 99;} 
        string get_name_2(){return "";}

        string get_output_name_2(){return "";}
        string get_output_name_3(){return "";}
        string get_output_name_4(){return "";}
        
        void set_output_value_2(int x){ }
        void set_output_value_3(int x){ }
        void set_output_value_4(int x){ }

        int get_output_value_2() { return -99;}
        int get_output_value_3() { return -99;}
        int get_output_value_4() { return -99;}

        void set_former_out(int x) { }
        int get_former_out_value(){ return -30;}

};
class Decoder : public Gate{
    public:
    string input1;//holds input1 name
    string input2;//holds input2 name
    //==============//
    string output1;//holds output1 name
    string output2;//holds output2 name
    string output3;//holds output3 name
    string output4;//holds output4 name
    //==============//
    string type;//holds class type
    //================//
    int data_input1;//holds input1 value
    int data_input2;//holds input2 value
    //================//
    int data_output1;//holds output1 value
    int data_output2;//holds output2 value
    int data_output3;//holds output3 value
    int data_output4;//holds output4 value

    Decoder(string out1,string out2,string out3,string out4,string in1,string in2)
    {
        //default settings
        output1 = out1;
        output2 = out2;
        output3 = out3;
        output4 = out4;
         //================//
        input1 = in1;
        input2 = in2;
        type = "Decoder";
         //================//
        data_output1 = -1;
        data_output2 = -1;
        data_output3 = -1;
        data_output4 = -1;
         //================//
         data_input1 = -1;
         data_input2 = -1;
    }
     //Performs calculations according to the given truth table and return output value
    int evaluation(){
        if(data_input1 == 0 && data_input2 == 0)
        {
            data_output1 =1;
            data_output2 =0;
            data_output3 =0;
            data_output4 =0;
        }
        else if(data_input1 == 0 && data_input2 == 1)
        {
            data_output1 =0;
            data_output2 =1;
            data_output3 =0;
            data_output4 =0;
        }
        else if(data_input1 == 1 && data_input2 == 0)
        {
            data_output1 =0;
            data_output2 =0;
            data_output3 =1;
            data_output4 =0;
        }
        else if(data_input1 == 1 && data_input2 == 1)
        {
            data_output1 =0;
            data_output2 =0;
            data_output3 =0;
            data_output4 =1;
        }
        return 0;
     }
    string get_type(){ return type;}//returns class type
    //=============================//
    //Returns input1 and input2 values
    int get_value_1(){ return data_input1;}
    int get_value_2(){return data_input2;} 
    //==============================//
    //Sets input1 and input2 values
    void set_value_1(int x){ data_input1 = x;}
    void set_value_2(int x){ data_input2 = x;}
    //==============================//
    //Returns input1 name and input2 name
    string get_name_1(){return input1;}
    string get_name_2(){return input2;}
    //==============================//
    //Returns output1,output2,output3 and output4 names
    string get_output_name(){return output1;}
    string get_output_name_2(){return output2;}
    string get_output_name_3(){return output3;}
    string get_output_name_4(){return output4;}
    //==============================//
    //Sets output1,output2,output3 and output4 values
    void set_output_value(int x){ data_output1 = x;}
    void set_output_value_2(int x){ data_output2 = x;}
    void set_output_value_3(int x){ data_output3 = x;}
    void set_output_value_4(int x){ data_output4 = x;}
    //Returns output1,output2,output3 and output4 values
    int get_output_value_2() {return data_output2 ;}
    int get_output_value_3() {return data_output3 ;}
    int get_output_value_4() {return data_output4 ; }
    int get_output_value() {return data_output1; }

    //These functions are for other function
    void set_former_out(int x) { }
    int get_former_out_value(){ return -30;}
};
class Flipflop : public Gate
{
    public:

    string input_name;//holds input name
    string output_name;//holds output name

    string Type;//holds class type
    
    int input_value;//holds input value
    int former_out;//holds former out value
    int output_value;//holds output value
    
    
    Flipflop(string input,string output)
    {
        //Default settings
        Type = "Flipflop";
        input_name = input;
        output_name = output;
        input_value = -1;
        former_out = 0;
        output_value = -99;
    }
    

    int evaluation() {
        //Performs calculations according to the given truth table and return output value
        int result = -99; 
        if(input_value == former_out)
        {
            result = 0;
        }
        else if(input_value != former_out)
        {
            result = 1;
        }
        output_value = result;
        return result;
    }
    string get_type(){ return Type;}//Returns type 
    
    string get_name_1(){ return input_name;}//Returns input name
    string get_name_2(){ return "Former_out";}//Return former_out

    int get_value_1(){ return input_value;}//return input1 value
    int get_value_2(){ return former_out;}//Return former out value

    string get_output_name(){ return output_name;}//Returns output name

    int get_output_value() {return output_value; }//return output value
    void set_output_value(int x){ output_value = x;}//Sets output value

    
    void set_value_1(int x){input_value=x;}//sets input1 value
    void set_value_2(int x){former_out = x;}//sets former out value
    void set_former_out(int x) {former_out = x;}//sets former out value

    int get_former_out_value(){ return former_out;} //return former out value


    //==============================//
    //all functions below are empty  because of these functions are for other classes//
    
    string get_output_name_2(){return "";}
    string get_output_name_3(){return "";}
    string get_output_name_4(){return "";}

    void set_output_value_2(int x){ }
    void set_output_value_3(int x){ }
    void set_output_value_4(int x){ }

    int get_output_value_2() {return -99; }
    int get_output_value_3() { return -99;}
    int get_output_value_4() {return -99; }

};
#endif
