<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\controllers\components;


    /**
     * Component to handle achievements.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class AchievementComponent extends \nre\core\Component
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('achievements', 'characterroles');




        /**
         * Construct a new Achievements-component.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Check for newly achieved Achievements.
         *
         * @param   int     $seminaryId         ID of Seminary to check Achievements for
         * @param   int     $characterId        ID of Character to check Achievements for
         * @param   array   $checkConditions    Conditions to check
         * @return  array                       List of newly achieved achievements
         */
        public function checkAchievements($seminaryId, $characterId, $checkConditions=null)
        {
            // Set conditions to check
            if(!is_null($checkConditions) && !is_array($checkConditions)) {
                $checkConditions = array($checkConditions);
            }

            // Get unachieved Achievments
            $achievements = $this->Achievements->getUnachhievedAchievementsForCharacter($seminaryId, $characterId);
            // Merge “only-once” Achievements
            if(in_array('user', $this->Characterroles->getCharacterrolesForCharacterById($characterId))) {
                $achievements = array_merge($achievements, $this->Achievements->getUnachievedOnlyOnceAchievementsForSeminary($seminaryId));
            }

            // Check conditions
            $achievedAchievements = array();
            foreach($achievements as &$achievement)
            {
                // Check condition to test
                if(!is_null($checkConditions) && !in_array($achievement['condition'], $checkConditions)) {
                    continue;
                }

                // Check deadline
                if(!is_null($achievement['deadline']) && $achievement['deadline'] < date('Y-m-d H:i:s')) {
                    continue;
                }

                // Get conditions
                $conditions = array();
                $progress = 0;
                switch($achievement['condition'])
                {
                    // Date conditions
                    case 'date':
                        $conditionsDate = $this->Achievements->getAchievementConditionsDate($achievement['id']);
                        foreach($conditionsDate as &$condition)
                        {
                            $conditions[] = array(
                                'func'      => 'checkAchievementConditionDate',
                                'params'    => array(
                                    $condition['select']
                                )
                            );
                        }
                    break;
                    // Character conditions
                    case 'character':
                        $conditionsCharacter = $this->Achievements->getAchievementConditionsCharacter($achievement['id']);
                        foreach($conditionsCharacter as &$condition)
                        {
                            $conditions[] = array(
                                'func'      => 'checkAchievementConditionCharacter',
                                'params'    => array(
                                    $condition['field'],
                                    $condition['value'],
                                    $characterId
                                )
                            );
                        }
                    break;
                    // Quest conditions
                    case 'quest':
                        $conditionsQuest = $this->Achievements->getAchievementConditionsQuest($achievement['id']);
                        foreach($conditionsQuest as &$condition)
                        {
                            $conditions[] = array(
                                'func'      => 'checkAchievementConditionQuest',
                                'params'    => array(
                                    $condition['field'],
                                    $condition['count'],
                                    $condition['value'],
                                    $condition['status'],
                                    $condition['groupby'],
                                    $condition['quest_id'],
                                    $characterId
                                )
                            );
                        }
                    break;
                    // Achievement conditions
                    case 'achievement':
                        $conditionsAchievement = $this->Achievements->getAchievementConditionsAchievement($achievement['id']);
                        foreach($conditionsAchievement as &$condition)
                        {
                            $conditions[] = array(
                                'func'      => 'checkAchievementConditionAchievement',
                                'params'    => array(
                                    $condition['field'],
                                    $condition['count'],
                                    $condition['value'],
                                    $condition['groupby'],
                                    $condition['meta_achievement_id'],
                                    $characterId
                                )
                            );
                        }
                    break;
                }

                // Do not achieve Achievements without conditions
                if(empty($conditions)) {
                    continue;
                }

                // Check conditions
                $achieved = ($achievement['all_conditions'] == 1);
                foreach($conditions as &$condition)
                {
                    // Calculate result of condition
                    $result = call_user_func_array(
                        array(
                            $this->Achievements,
                            $condition['func']
                        ),
                        $condition['params']
                    );

                    // The overall result and abort if possible
                    if($achievement['all_conditions'])
                    {
                        if(!$result) {
                            $achieved = false;
                            break;
                        }
                    }
                    else
                    {
                        if($result) {
                            $achieved = true;
                            break;
                        }
                    }

                }

                // Achievement achieved
                if($achieved)
                {
                    // Set status
                    $this->Achievements->setAchievementAchieved($achievement['id'], $characterId);

                    // Add to list
                    $achievedAchievements[] = $achievement;
                }
            }


            // Return newly achieved Achievements
            return $achievedAchievements;
        }

    }

?>
