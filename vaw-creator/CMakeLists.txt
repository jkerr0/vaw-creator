# CMakeList.txt: projekt CMake dla elementu vaw-creator, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#

# Dodaj źródło do pliku wykonywalnego tego projektu.
add_executable (vaw-creator "vaw-creator.cpp" "vaw-creator.h" "vaw-writer.h" "vaw-writer.cpp"  "vaw-format.h" "vaw-format.cpp" "wave-generator.h" "wave-generator.cpp" "creator-parameters.h" "creator-parameters.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET vaw-creator PROPERTY CXX_STANDARD 20)
endif()

# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
