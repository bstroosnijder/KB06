#include <iostream>

/**
	@namespace	TestNamespace	Lange beschrijving over de namespace
	@brief						Korte beschrijving over de namespace
*/
namespace TestNamespace
{
	/**
		@brief		Brief is een korte beschrijving (regel 1).
					Short is hetzelfde als Brief (regel 2).\n
					Met \\n kan een nieuwe regel begonnen worden (regel 3).
	
		Een losse regel tekst !
		Nog een losse regel tekst zonder lege regel !

		@code{.cpp}
			int main()
			{
				std::cout << "Een C++ code block!" << std::endl;
			}
		@endcode

		@code{.py}
			int main()
			{
				std::cout << "Een Python code block!" << std::endl;
			}
		@endcode

		\\b Maakt \b dik !

		\\e Maakt \e schuin !

		\\p maakt een \p argument en nog een \p argument !

		Gebruik een \\ voor een vreemd teken om deze te tonen. Zoals: \\\@ \\\\ \\\*

		@author	Michel van Os
		@version 1.0
		@todo Todo om aan te geven dat er nog iets gedaan moet worden. Todo's zijn zichtbaar bij related pages !
		@note Gewoon een melding in de documentatie =) !
		@param	par1	De 1e parameter
		@param	par2	De 2e parameter
		@param	par3	De 3e parameter
		@return NULL
	*/
	class TestClass
	{

	};
}


/*! \brief Brief description.
 *         Brief description continued.
 *
 *  Detailed description starts here.
 */
int main(int p_argCount, char** argArray)
{
	std::cout << "Hello World!" << std::endl;

	std::system("PAUSE");

	return 0;
}