#ifndef _INTERFACE_h
#define _INTERFACE_h

class Interface 
{
protected:
	
public:
	virtual bool is_active() = 0;
	virtual uint8_t Available() = 0;
	virtual void Begin(uint32_t speed) = 0;
	virtual void Writeln(String str) = 0;
	virtual void Write(String str) = 0;
	virtual char Read() = 0;
	virtual ~Interface() = default;
	
};

// PIN = 4

class SerialInterface : public Interface
{
private:
	uint8_t PIN;
	bool active;
public:
	SerialInterface(uint8_t PIN = 4)
	{
		this->PIN = PIN;
		active = false;
	}

	bool is_active() override
	{
		if (digitalRead(PIN))
		{
			return true;
		}
		else
		{
			return  false;
		}
	}

	void Begin(uint32_t speed) override
	{
		Serial.begin(speed);
	}

	uint8_t Available() override
	{
		return Serial.available();
	}
		
	void Writeln(String str) override
	{
		Serial.println(str);
	}

	void Write(String str) override
	{
		Serial.print(str);
	}

	char Read() override
	{
		return Serial.read();
	}
};

// PIN = 5

class SerialUSBInterface : public Interface
{
private:
	uint8_t PIN;
	bool active;
public:
	SerialUSBInterface(uint8_t PIN = 5)
	{
		this->PIN = PIN;
		active = false ;
	}

	bool is_active() override
	{
		if (digitalRead(PIN))
		{
			return true;
		}
		else
		{
			return  false;
		}
	}

	uint8_t Available() override
	{
		return SerialUSB.available();
	}

	void Begin(uint32_t speed) override
	{
		SerialUSB.begin(speed);
	}

	void Writeln(String str) override
	{
		SerialUSB.println(str);
	}

	void Write(String str) override
	{
		SerialUSB.print(str);
	}

	char Read() override
	{
		return SerialUSB.read();
	}
};

// PIN = 6

class EthernetInterface : public Interface
{
private:
	uint8_t PIN;
	bool active;
public:
	EthernetInterface(uint8_t PIN = 6)
	{
		this->PIN = PIN;
		active = false;
	}

	bool is_active() override
	{
		
	}
	
	uint8_t Available() override
	{
	}
	void Begin(uint32_t speed) override
	{
	}

	void Writeln(String str) override
	{
	}

	void Write(String str) override
	{
	}

	char Read() override
	{
	}
};

#endif

