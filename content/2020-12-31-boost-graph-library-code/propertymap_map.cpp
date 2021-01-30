#include <iostream>
#include <map>
#include <string>
#include <boost/property_map/property_map.hpp>

using namespace std;

int main(void)
{
  // On commence avec une map classique :
  map<string, string> name2address;
  name2address.insert({"Fred", "The Burrow, England"});
  name2address.insert({"George", "The Burrow, England"});

  // Construction d'une PropertyMap, en utilisant la map classique comme storage :
  boost::associative_property_map< map<string, string> > address_pmap(name2address);

  // À partir de maintenant, la PropertyMap présente une interface de type dictionnaire sur son storage.

  // lecture :
  string fred_old_address = get(address_pmap, "Fred");
  cout << "Until now, Fred lived in : " << fred_old_address << endl;

  // écriture :
  put(address_pmap, "Fred", "Somewhere else...");
  cout << "But from now on, Fred lives : " << name2address["Fred"] << endl;

  // référence + operator[] :
  string& george_address = address_pmap["George"];
  george_address = "Alone";
  cout << "And George is now : " << name2address["George"] << endl;

  return EXIT_SUCCESS;
}
