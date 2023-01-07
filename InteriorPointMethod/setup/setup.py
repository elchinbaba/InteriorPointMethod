from distutils.core import setup, Extension

def main():
    setup(name="optimize",
          version="1.0.0",
          description="Python module that returns the solution of the Convext Optimization Linear Programming problem",
          author="Babali Elchin",
          author_email="babalielchin@gmail.com",
          ext_modules=[Extension("optimize", ["setup.cpp"])])

if __name__ == "__main__":
    main()