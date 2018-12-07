#include "MD5.h"

MD5::MD5(string inputStr) {
	this->init(inputStr);
	this->MD5Encode();
	this->to_resultStr();
}

MD5::~MD5() {
	delete this->srcData;
}

void MD5::init(string inputStr) {
	this->srcStr = inputStr;
	this->resultStr = string(128, ' ');
	this->buffer[0] = 0x67452301;
	this->buffer[1] = 0xefcdab89;
	this->buffer[2] = 0x98badcfe;
	this->buffer[3] = 0x10325476;
	
	int len = inputStr.size() + 1, i = 0, digestLen = 0;
	bit32 tempLen = inputStr.size() * 8;
	bit64 tempLen2 = inputStr.size() * 8;
	while(len % 64 != 56)	len++;
	len += 8;
	this->srcData = new bit8[len];
	for(i = 0; i < inputStr.size(); ++i)
		this->srcData[i] = (bit8)inputStr[i];
	this->srcData[i] = (bit8)0x80;
	for(i = i + 1; i < len; ++i)
		this->srcData[i] = 0x00;
	this->numOfLoop = len / 64;	
	for(int i = 0; i < 8; ++i)
		this->srcData[len - 8 + i] = (bit8)(tempLen2 >> (8*i));
}

void MD5::MD5Encode() {
	for(int i = 0; i < this->numOfLoop; ++i) {
		bit32 block[16];
		bit8 tempBlock[64];
		memcpy(tempBlock, this->srcData + 64*i, 64*sizeof(bit8));
		this->to_bit32(tempBlock, block, 64);
		this->HMD5Func(block);
	}
}

void MD5::to_bit32(const bit8 *inputData, bit32 *outputData, size_t length) {
	for(int i = 0, count = 0; i < length; i += 4, ++count)
		outputData[count] = ((bit32)inputData[i]) | 
						((bit32)inputData[i + 1] << 8) | 
						((bit32)inputData[i + 2] << 16) | 
						((bit32)inputData[i + 3] << 24);
}

void MD5::HMD5Func(const bit32 block[16]) {
	bit32 a = this->buffer[0], b = this->buffer[1], c = this->buffer[2], d = this->buffer[3];
	auto switchData = [](bit32 &a, bit32 &b, bit32 &c, bit32 &d) {
		bit32 temp = b;
		b = a;
		a = d;
		d = c;
		c = temp;	
	};
	for(int i = 0; i < 16; ++i) {
		int k = i, count = i % 4;
		FF(a, b, c, d, block[k], s[0][count], T[0][i]);
		switchData(a, b, c, d);
	}
	for(int i = 0; i < 16; ++i) {
		int k = (5*i + 1) % 16, count = i % 4;
		GG(a, b, c, d, block[k], s[1][count], T[1][i]);
		switchData(a, b, c, d);
	}
	for(int i = 0; i < 16; ++i) {
		int k = (3*i + 5) % 16, count = i % 4;
		HH(a, b, c, d, block[k], s[2][count], T[2][i]);
		switchData(a, b, c, d);
	}
	for(int i = 0; i < 16; ++i) {
		int k = 7*i % 16, count = i % 4;
		II(a, b, c, d, block[k], s[3][count], T[3][i]);
		switchData(a, b, c, d);
	}
	this->buffer[0] += a;
	this->buffer[1] += b;
	this->buffer[2] += c;
	this->buffer[3] += d;
}

void MD5::to_resultStr() {
	auto toHex = [](int inputNum) -> char {
		if(inputNum >= 0 && inputNum < 10)
			return (inputNum + '0');
		else if(inputNum >= 10 && inputNum < 16)
			return (char)(inputNum + 55);
		else	return ' ';		
	};
	int count = 0;
	for(int i = 0; i < 4; ++i) {
		bool boolArray[32];
		for(int j = 0; j < 32; ++j)
			boolArray[31 - j] = (this->buffer[i] >> j) % 2;
		for(int j = 3; j >= 0; --j, count += 2) {
			int tempNum1 = 0, tempNum2 = 0;
			for(int k = 0; k < 4; ++k) {
				tempNum1 += boolArray[8*j + k] * pow(2, 3 - k);
				tempNum2 += boolArray[8*j + k + 4] * pow(2, 3 - k);
			}
			char tempchar1 = toHex(tempNum1), tempchar2 = toHex(tempNum2);
			this->resultStr[count] = tempchar1;
			this->resultStr[count + 1] = tempchar2;
		}
	}
}

string MD5::getResultStr() const {
	return this->resultStr;
}