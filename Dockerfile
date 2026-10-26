FROM gcc:12 AS compiler

RUN apt-get update \
    && apt-get install -y libssl-dev make
COPY hasheur.c /home/
COPY dico.txt /home/dico.txt

RUN gcc /home/hasheur.c -o /home/t3c

RUN echo "check"
