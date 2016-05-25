#include <iostream>

#include <json/json.h>

#include "Person.h"
#include "JsonCast.h"

int main()
{
    Person person;
    person.age = 25;
    person.salary = 3.50f;
    person.name = "Ron Burgandy"; // I'm a person!
    person.favouriteMovies["Nostalgia Critic"] = { MovieInfo{ "The Room", 8.5f } };
    person.favouriteMovies["John Tron"] = { MovieInfo{"Goosebumps", 10.0f },
                                            MovieInfo{ "Talking Cat", 9.0f } };

    // And here's how you can serialize/deserialize
    // (if you write a function for your type. I wrote it for Json::Value! ;D)
    Json::Value root;
    serialize(person, root);

    Person person2;
    deserialize(person2, root); // set values from Json::Value

    std::cout << root << std::endl;

    system("pause");
}