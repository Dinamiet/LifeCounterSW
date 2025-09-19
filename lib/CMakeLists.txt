cmake_minimum_required(VERSION 3.20.0)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
	Scheduler
	GIT_REPOSITORY
		git@github.com:Dinamiet/Scheduler.git
	GIT_TAG
		main
	SOURCE_DIR
		${CMAKE_SOURCE_DIR}/lib/Scheduler
)

FetchContent_Declare(
	Observer
	GIT_REPOSITORY
		git@github.com:Dinamiet/Observer.git
	GIT_TAG
		main
	SOURCE_DIR
		${CMAKE_SOURCE_DIR}/lib/Observer
)

FetchContent_MakeAvailable(
	Scheduler
	Observer
)
