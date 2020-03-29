# BASE de dados generica y tabelas para casi todos os juegos simples que pude imaginar

DROP DATABASE IF EXISTS GameSO;
CREATE DATABASE GameSO;
USE GameSO;

CREATE TABLE Player(
	Username VARCHAR(25) NOT NULL PRIMARY KEY,
	Password CHAR(32) NOT NULL,
	#Password VARCHAR(25) NOT NULL,
	Ativo TINYINT(1) DEFAULT 1
);

CREATE TABLE Game(
	ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
	Inicio TIMESTAMP NOT NULL DEFAULT NOW(),
	Fim TIMESTAMP NOT NULL DEFAULT NOW(),
	Vencedor VARCHAR(25),
	Ativo TINYINT(1) DEFAULT 1,
	FOREIGN KEY (Vencedor) REFERENCES Player(Username)
)AUTO_INCREMENT = 1;

CREATE TABLE Relaciona(
	ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
	Game INT NOT NULL,
	Player VARCHAR(25),
	Score INTEGER NOT NULL DEFAULT 0,
	FOREIGN KEY (Player) REFERENCES Player(Username),
	FOREIGN KEY (Game) REFERENCES Game(ID)
)AUTO_INCREMENT = 1;

#INSERT INTO Player (Username, Password) VALUES ('Jose', '1qaz2wsx');
#INSERT INTO Player (Username, Password) VALUES ('Luiz', '2wsx3edc');

#INSERT INTO Game () VALUES ();

#INSERT INTO Relaciona (Game,Player) VALUES (1,'Jose');
#INSERT INTO Relaciona (Game,Player) VALUES (1,'Luiz');

# mysql> INSERT INTO md5_test_char (`md5`) VALUES ('0800fc577294c34e0b28ad2839435945');

# `md5` CHAR(32) NOT NULL,



