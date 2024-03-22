# **`CDebug`**
`CDebug` - is a tool for displaying debugging information on the console screen. 
It also stores information about the latest messages, whether just information, warnings or errors.

## Setting up `CDebug`
### Build with `CMake`
```shell
# After you've downloaded the library...
~/dev~~~~~~~$ cd $PATH_TO_THE_LIBRARY_DIR/
~/dev/CDebug$ cmake -B $BUILD_DIR -S . \
                    -DCMAKE_BUILD_TYPE=$BUILD_CONFIG \
                    -DBUILD_SHARED_LIBS=TRUE
~/dev/CDebug$ cmake --build $BUILD_DIR \
                    --config $BUILD_CONFIG
~/dev/CDebug$ cmake --install $BUILD_DIR \
                    --config $BUILD_CONFIG
```
### Link to your project
```cmake
find_package(CDebug REQUIRED)
link_libraries(CDebug::cdebug)
```