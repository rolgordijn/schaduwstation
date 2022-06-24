#pragma once

#include <MCP23017.h>


class IO {
  protected:
    uint8_t pin;
    bool tris;
    bool state;
    bool changed;
  public:
    IO() {
    }

    virtual void setHigh() = 0;
    virtual void setLow()  = 0;
    virtual bool getValue() = 0;
    virtual void setValue(bool val) = 0;

    virtual void setInput()  = 0;
    virtual void setOutput()  = 0;
    virtual void setPinMode(bool dir) =   0;
    virtual bool getPinMode (void) = 0;

    bool pinStateChanged(void){
      return changed;
    }

};


class BasicIO : public IO {
  public:


    BasicIO(): IO() {
    }

    

    
    BasicIO(int pin, int tris, int val): IO() {
      this->pin = pin;
      // pinMode(pin, tris);
      //digitalWrite(pin, val);
    }

    BasicIO(int pin, int tris): IO() {
      this->pin = pin;
      //pinMode(pin, tris);
      //digitalWrite(pin, 0);
    }



    void setHigh(void) {
      digitalWrite(pin, HIGH);

    }
    void setLow(void) {
      digitalWrite(pin, LOW);
    }

    bool getValue() {
      bool val = digitalRead(pin);
      changed = val != state;
      state = val; 
      return state;
    }

    void setValue(bool val) {
      digitalWrite(pin, val);
    }

    void setInput() {
      pinMode(pin, INPUT);
    }
    void setOutput() {
      pinMode(pin, OUTPUT);
    }

    void setPinMode(bool dir) {
      pinMode(pin, dir);
    }

    bool getPinMode(void) {
      return 0; // not implemented yet? How?
    }

};

class MCP23017IO : public IO {
  private:
    MCP23017 * ic;
  public:
    MCP23017IO(): IO() {
      this->pin = pin;
      this->ic = ic;
      //ic->pinMode(pin, tris);
      //ic->digitalWrite(pin, val);
    }


    MCP23017IO(MCP23017 * ic, uint8_t pin, bool tris, bool val): IO() {
      this->pin = pin;
      this->ic = ic;
      //ic->pinMode(pin, tris);
      //ic->digitalWrite(pin, val);
    }

    MCP23017IO(MCP23017 * ic, uint8_t pin, bool tris): IO() {
      this->pin = pin;
      this->ic = ic;
      //ic->pinMode(pin, tris);
      //ic->digitalWrite(pin, 0);
    }

    void setHigh(void) {
      ic->digitalWrite(pin, HIGH);

    }
    void setLow(void) {
      ic->digitalWrite(pin, LOW);
    }

    bool getValue() {
      bool val = ic->digitalRead(pin);
      changed = val != state;
      state = val; 
      return state;
    }

    void setValue(bool val) {
      ic->digitalWrite(pin, val);
    }

    void setInput() {
      ic->pinMode(pin, INPUT);
    }
    void setOutput() {
      ic->pinMode(pin, OUTPUT);
    }

    void setPinMode(bool dir) {
      ic->pinMode(pin, dir);
    }

    bool getPinMode(void) {
      return 0; // not implemented yet? How?
    }

};


class VirtualIO : public IO {
  public:


    VirtualIO(): IO() {
      state = 0;
    }

    void setHigh(void) {
      state = 1;
    }
    void setLow(void) {
      state = 0;
    }

    bool getValue() {
      bool val = state;
      changed = val != state;
      state = val; 
      return state;
    }

    void setValue(bool val) {
      state = val;
    }

    void setInput() {
     
    }
    void setOutput() {
      
    }

    void setPinMode(bool dir) {
    }

    bool getPinMode(void) {
      return 0; // not implemented yet? How?
    }

};
