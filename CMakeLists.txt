add_library(htu21df
	htu21df.c
)

target_include_directories(htu21df PUBLIC
	.
)

target_link_libraries(htu21df pico_stdlib hardware_i2c)