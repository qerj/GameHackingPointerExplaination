#include <iostream>
#include <Windows.h>

class playa
{
public:
	int ammo = 1; //0x0;
	int armor = 50; //0x4
	int health = 100; 

	void printDMAA()
	{
		std::cout << "ammo: " << &ammo << std::endl;
		std::cout << "armor: " << &armor << std::endl;
		std::cout << "health: " << &health << std::endl;
	}
};

int main()
{
	uintptr_t a = 12;

	//since we casted this to a pointer
	//its now pointer to some memory which we can deference 
	//in the address space to get a value from.
	//pretend yes is a pointer to a class
	//in assault cube this is a real address base address(ac_client.exe) + 0x10f4f4
	//0x50f4f4 is our local player class pointer. with that we can offset a number from the start
	//of the pointer to get a variable if we knew the offset.
	//with 0x50f4f4 being a pointer if we offset 0xF8 from it we will get the health address
	//now 0x50f4f4 + 0xF8 will return a pointer in this case. we want the value
	//so now we will dereference the address of the pointer to get the value, 
	//Make sure its nots a null pointer :)
	uintptr_t* yes = (uintptr_t*)(0x00400000 + 0x10f4f4);
	//for future reference please take a look at the virtual address table (VAT)

	//time for real use

	//here is another form of a pointer but in a real world programming occurrence.
	uintptr_t* yes2 = &a; //pretend here that '&a' is 0x00400000 + 0x10f4f4
	std::cout << yes2 << std::endl; //if we derefence the yes2 pointer we will get the value of 'a'
	//which would be the start of the player class pointer in assault cube also giving us whatever the first member is in the class itself.

	//lets edit the pointer
	*yes2 = 500;

	//prints out 500
	std::cout << *yes2 << std::endl;
	//also prints out 500 since we edited the value that the memory was pointing at
	std::cout << a << std::endl;

	std::cout << std::endl;

	//ok now lets dig deep.
	playa* player = new playa;
	player->printDMAA(); //prints the real addresses of our player class member vars

	std::cout << std::endl;
	//make sure our player pointer is okay
	std::cout << "player pointer address: " << player << std::endl;

	//ok here is where things get confusing
	//pointer arithmetic with certain types can destroy your brain when you look at it.
	//heres the explination.
	//we have 2 cast so lets start from the back to the front.
	//(char*)player + 4 will make sure that when adding the 4 bytes to player pointer
	//it will give us the correct address, each char is 1 byte long which lets us 
	//do our pointer arithmetic correctly.
	//why our we casting it to a uintptr pointer, well that makes sure that when we
	//deference it we actually get the value thats inside the address itself.
	//casting it to a uintptr_t pointer will now let us dereference that address
	//and get the armor value.
	std::cout << "ammo deref: " << *(uintptr_t*)((char*)player) << std::endl;
	std::cout << "armor deref: " << *(uintptr_t*)((char*)player + + 4) << std::endl;
	std::cout << "health deref: " << *(uintptr_t*)((char*)player + 8) << std::endl;

	delete(player);
}
