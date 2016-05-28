<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\models;


    /**
     * Model to interact with characterroles-table.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class CharacterrolesModel extends \hhu\z\Model
    {




        /**
         * Construct a new CharacterrolesModel.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Get all characterroles for a Character referenced by its ID.
         *
         * @param   int     $characterId    ID of Character
         * @return  array                   Characterroles for a Character
         */
        public function getCharacterrolesForCharacterById($characterId)
        {
            return $this->db->query(
                'SELECT characterroles.id, characterroles.created, characterroles.name '.
                'FROM characters_characterroles '.
                'LEFT JOIN characterroles ON characterroles.id = characters_characterroles.characterrole_id '.
                'WHERE characters_characterroles.character_id = ?',
                'i',
                $characterId
            );
        }


        /**
         * Add a role to a Character.
         *
         * @param   int     $characterId    ID of Character to add role to
         * @param   string  $characterrole  Role to add
         */
        public function addCharacterroleToCharacter($characterId, $characterrole)
        {
            $this->db->query(
                'INSERT IGNORE INTO characters_characterroles '.
                '(character_id, characterrole_id) '.
                'SELECT ?, id '.
                'FROM characterroles '.
                'WHERE name = ?',
                'is',
                $characterId,
                $characterrole
            );
        }


        /**
         * Remove a role from a Character.
         *
         * @param   int     $characterId    ID of Character to remove role from
         * @param   string  $characterrole  Role to remove
         */
        public function removeCharacterroleFromCharacter($characterId, $characterrole)
        {
            $this->db->query(
                'DELETE FROM characters_characterroles '.
                'WHERE character_id = ? AND characterrole_id = ('.
                    'SELECT id '.
                    'FROM characterroles '.
                    'WHERE name = ?'.
                ')',
                'is',
                $characterId,
                $characterrole
            );
        }

    }

?>
