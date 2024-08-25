cmake_minimum_required(VERSION 3.5)

project(06.containers)

add_executable(test_containers
        main.cpp
        containers/base_container.h
        containers/vector_iterator.hpp
        containers/fixed_size_container.hpp
        containers/dynamic_container.hpp
        containers/bidirectional_list_container.hpp
        containers/bidirectional_list_iterator.hpp
        containers/bidirectional_data_node.hpp
)

set_target_properties(test_containers PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)