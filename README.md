# Popis projektu
Projekt do PGR. Hra, která je silně inspirovaná wolfenstein 3D.

[![video](https://img.youtube.com/vi/N49cnhM3bg0/0.jpg)](https://www.youtube.com/watch?v=N49cnhM3bg0)

# Použité technologie
Celá hra je napsaná v c++ s pomocí opengl 3.1 core profile. Použité knihovny:
* [Bullet](http://bulletphysics.org/)
* [glm](https://glm.g-truc.net)
* [SDL2](https://www.libsdl.org/)
* [DevIl](http://openil.sourceforge.net/)
* [GLEW](http://glew.sourceforge.net/)
* [ASSIMP](www.assimp.org)
* [EntityX](https://github.com/alecthomas/entityx)
* [json](https://github.com/nlohmann/json)

# Možnosti enginu
* Nahrávání mapy (grafický + kolizní model)
* Nahrávání entit s pomocí jsonu (+ plugin do blenderu pro jeho snadné generování)

# Sestavení
```
cmake .
make
```
