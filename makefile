# Répertoires
BINDIR=./BIN
INCLUDEDIR=./INCLUDE
LIBDIR=./LIB
OBJDIR=./OBJ
SRCDIR=./SRC

LISTELIB=libliste
GRAPHELIB=libgraphe

#
CC=gcc
IFLAGS=-I$(INCLUDEDIR)
LFLAGS=-L$(LIBDIR)
LLIB=-lgraphe -lliste

SL=ar rcs

#
LISTEOBJ=$(OBJDIR)/MaListe.o
GRAPHEOBJ=$(OBJDIR)/Graphe.o

EXEC=Run
MAIN=$(BINDIR)/$(EXEC)

# Cible proncipale
all: libs $(MAIN)

#
$(MAIN): $(BINDIR)
	$(CC) ${SRCDIR}/main.c ${SRCDIR}/interface.c $(IFLAGS) $(LFLAGS) $(LLIB) -o $@ 

#########################################
# BIBLIOTHÈQUES
#########################################

# Règle de construction des bibliothèques
libs: $(LISTELIB) $(GRAPHELIB)

# Règle de construction de MaListe.a
$(LISTELIB): $(LISTEOBJ) $(LIBDIR)
	$(SL) $(LIBDIR)/$@.a $<

# Règle de construction de Graphe.a
$(GRAPHELIB): $(GRAPHEOBJ) $(LIBDIR)
	$(SL) $(LIBDIR)/$@.a $<

# Règle de construction de MaListe.o
$(LISTEOBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDEDIR)/%.h $(OBJDIR)
	$(CC) $(IFLAGS) -c $< -o $@

# Règle de construction de Graphe.o
$(GRAPHEOBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDEDIR)/%.h $(OBJDIR)
	$(CC) $(IFLAGS) -c $< -o $@

#########################################
# Règles de construction des répertoires
$(BINDIR):
	mkdir $(BINDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(LIBDIR):
	mkdir $(LIBDIR)

#########################################
# Règles de nettoyage
clean:
	rm $(OBJDIR)

veryclean: clean
	rm $(LIBDIR)
