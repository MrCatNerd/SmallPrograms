# pygame basic window
import pygame
import time
import sys

from settings import *


class Main:
    def __init__(self) -> None:
        self.app = pygame.display.set_mode((WIDTH, HEIGHT))
        pygame.display.set_caption(TITLE)

        self.run: bool = True

        self.clock = pygame.time.Clock()

    def play(self) -> None:
        last_time = time.time()
        while self.run:
            deltaTime: float = time.time() - last_time
            last_time = time.time()

            self.app.fill("grey")

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.quit()
                elif event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                    self.quit()

            self.clock.tick()
            pygame.display.update()

    def quit(self) -> None:
        self.run = False
        pygame.quit()
        sys.exit()


if __name__ == "__main__":
    main = Main()
    main.play()
