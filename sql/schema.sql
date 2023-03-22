CREATE TABLE IF NOT EXISTS users
(
    user_id  serial PRIMARY KEY NOT NULL,
    username varchar(40) UNIQUE NOT NULL
);

CREATE TABLE IF NOT EXISTS tokens
(
    token_id      serial      NOT NULL PRIMARY KEY,
    token_val     TEXT UNIQUE NOT NULL,
    creation_date timestamp   NOT NULL DEFAULT NOW()
);

CREATE TABLE IF NOT EXISTS user_to_token
(
    user_id  bigint REFERENCES users (user_id)   ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,
    token_id bigint REFERENCES tokens (token_id) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL
);


CREATE VIEW UserToTokenKV
AS
SELECT username, token_val, creation_date
FROM user_to_token
         LEFT JOIN users USING (user_id)
         LEFT JOIN tokens USING (token_id);

