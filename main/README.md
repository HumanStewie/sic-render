# The entry point of [sic]render

This is where we start and initialize all services for the engine. It also holds the main render loop.

The general flow we are looking for is main -> GameEngine -> RenderingEngine -> `drivers`