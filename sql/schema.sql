CREATE TABLE IF NOT EXISTS users
(
    user_id serial PRIMARY KEY,
    email   varchar(40) UNIQUE NOT NULL
);


CREATE TABLE IF NOT EXISTS tokens
(
    token_id  serial PRIMARY KEY,
    token_val TEXT UNIQUE NOT NULL
);

CREATE TABLE IF NOT EXISTS users_to_token
(
    user_id  bigint REFERENCES users (user_id) ON DELETE CASCADE,
    token_id bigint REFERENCES tokens (token_id) ON DELETE CASCADE
);

CREATE VIEW UserToTokenVW
AS
SELECT email, token_val
FROM users_to_token
    LEFT JOIN users USING (user_id)
    LEFT JOIN tokens USING (token_id);